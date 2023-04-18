#include "TextureDisplay.h"
#include <iostream>
#include <random>

#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/IconObject/IconObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Gameobjects/Utilities/PNGObject.h"
#include "Threads/GlobalSemaphore.h"
#include "Threads/ThreadLoader.h"
#include "Threads/ThreadPool.h"
#include "Utilities/Manager/TextureManager.h"


TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

TextureDisplay::~TextureDisplay()
{
	delete guard;
	delete condition_delete;
	delete condition_insert;
	delete condition_search;

	for (auto icon : displayedIcons) {
		delete icon;
	}
	displayedIcons.clear();
	for (auto icon : iconBank) {
		delete icon;
	}
	iconBank.clear();

	delete threadPool;

	delete lastDeletedIcon;
}

void TextureDisplay::Initialize()
{
	guard = new Mutex();
	condition_delete = new Condition();
	condition_insert = new Condition();
	condition_search = new Condition();

	mutex = new GlobalSemaphore(1, 1);
	deleterSem = new GlobalSemaphore(MAX_DELETER, MAX_DELETER);
	inserterSem = new GlobalSemaphore(0, MAX_INSERTER);

	lastDeletedIcon = new ICON_struct{0,0,"name", 0};

	// arrows
	for (int i = 0; i < 4; ++i)
	{
		PNGObject* arrow = new PNGObject("green_icon");
		GameObjectManager::GetInstance()->AddObject(arrow);
		green_arrows.emplace_back(arrow);
		arrow->SetPosition(-IMG_WIDTH, IMG_HEIGHT * 3);
	}
	for (int i = 0; i < 2; ++i)
	{
		PNGObject* arrow = new PNGObject("orange_icon");
		GameObjectManager::GetInstance()->AddObject(arrow);
		orange_arrows.emplace_back(arrow);
		arrow->SetPosition(-IMG_WIDTH, IMG_HEIGHT * 3);
	}
	red_arrow = new PNGObject("red_icon");
	GameObjectManager::GetInstance()->AddObject(red_arrow);
	red_arrow->SetPosition(-IMG_WIDTH, IMG_HEIGHT * 2);

	TextureManager::GetInstance()->LoadStreamingAssets();
	ConvertIconsToObjs();
	DisplaySetIcons();

	threadPool = new ThreadPool("SID_ThreadPool", 10);
	threadPool->StartScheduler();

	// run threads for 'deleter'
	for (int i = 0; i < MAX_DELETER; ++i)
	{
		CallDelete(i);
	}
	// run threads for 'inserter'
	for (int i = 0; i < MAX_INSERTER; ++i)
	{
		CallInsert(i);
	}
	// run threads for 'searcher'
	for (int i = 0; i < MAX_SEARCHER; ++i)
	{
		CallSearch(i);
	}
}

void TextureDisplay::ProcessInput(sf::Event event)
{
	
}

void TextureDisplay::Update(sf::Time deltaTime)
{
	/*this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
	
	//<code here for spawning icon object periodically>
	if (streamingType == StreamingType::BATCH_LOAD && !startedStreaming && ticks > STREAMING_LOAD_DELAY)
	{
		startedStreaming = true;
		ticks = 0.0f;
		TextureManager::GetInstance()->LoadStreamingAssets(this);
	}
	else if (streamingType == StreamingType::SINGLE_STREAM && ticks > STREAMING_LOAD_DELAY)
	{
		ticks = 0.0f;
		TextureManager::GetInstance()->LoadSingleStreamAsset(numDisplayed, this);
		numDisplayed++;
	}*/
}

void TextureDisplay::onFinishedExecution()
{

}

void TextureDisplay::OnSearch(int ID)
{
	while (true)
	{
		TrySearch(ID);
	}
}

void TextureDisplay::OnInsert(int ID)
{
	while (true)
	{
		TryInsert(ID);
	}
}


void TextureDisplay::OnDelete(int ID)
{
	while (true)//
	{
		TryDelete(ID);
	}
}

void TextureDisplay::CallSearch(int ID)
{
	ThreadLoader* iconSearcher = new ThreadLoader(ID, SID_ENUM::SEARCH, this);
	threadPool->ScheduleTask(iconSearcher);
}

void TextureDisplay::CallInsert(int ID)
{
	ThreadLoader* iconInserter = new ThreadLoader(ID, SID_ENUM::INSERT, this);
	threadPool->ScheduleTask(iconInserter);
}

void TextureDisplay::CallDelete(int ID)
{
	ThreadLoader* iconDeleter = new ThreadLoader(ID, SID_ENUM::DELETE, this);
	threadPool->ScheduleTask(iconDeleter);
}

void TextureDisplay::TrySearch(int ID)
{
	
	// critical-section
    // Create a random number generator engine
	std::mt19937 engine{ std::random_device{}() };
	// Create a uniform distribution
	std::uniform_int_distribution<int> dist{ 0, 10 - 1 };
	int random_num = dist(engine);
	
	// perform an arrow animation
	for (int i = 0; i < random_num; ++i)
	{
		std::cout << "Search: " << ID << ":" << random_num << std::endl;
		IETThread::sleep(500); // timer for showing the deleted icon(color indicator)
		// set position in the world
		float x = i * IMG_WIDTH;
		green_arrows[ID]->SetPosition(x, IMG_HEIGHT * 1.5f);
	}
	
}

void TextureDisplay::TryInsert(int ID)
{
	inserterSem->acquire();
	mutex->acquire();
	// random select an icon from the 'iconBank'
	std::srand(std::time(nullptr));
	int random_num = std::rand() % iconBank.size();

	// transfer the 'new' icon to the 'displayedIcons'
	IconObject* iconObject = iconBank[random_num];
	displayedIcons.emplace_back(iconObject);
	iconBank.erase(iconBank.begin() + random_num);
	iconBank.shrink_to_fit();
	// transfer the 'lastDeleted' icon to the 'iconBank'
	iconBank.emplace_back(displayedIcons[lastDeletedIcon->index]);
	displayedIcons.erase(displayedIcons.begin() + lastDeletedIcon->index);
	displayedIcons.shrink_to_fit();
	// show orange arrow
	for (int i = 0; i < MAX; ++i)
	{
		if (i == ID)
		{
			orange_arrows[ID]->SetPosition(lastDeletedIcon->pos_x, IMG_HEIGHT * (3.0f + 1.5f * (ID + 1) ));
			break;
		}
	}
	// enable and set the position based on the recently deleted icon
	iconObject->SetEnabled(true);
	iconObject->SetPosition(lastDeletedIcon->pos_x, lastDeletedIcon->pos_y);
	//std::cout << "Insert: " << lastDeletedIcon->pos_x << ":" << lastDeletedIcon->pos_y << std::endl;
	IETThread::sleep(500); // timer for showing the deleted icon(color indicator)

	mutex->release();
	deleterSem->release();
}

void TextureDisplay::TryDelete(int ID)
{
	deleterSem->acquire();
	mutex->acquire();
	
	// get the selected icon to be deleted
	std::srand(std::time(nullptr));
	int random_num = std::rand() % displayedIcons.size();
	IconObject* iconObject = displayedIcons[random_num];
	lastDeletedIcon->name = iconObject->GetName();
	lastDeletedIcon->pos_x = iconObject->GetPosition().x;
	lastDeletedIcon->pos_y = iconObject->GetPosition().y;
	lastDeletedIcon->index = random_num;
	// show red arrow
	red_arrow->SetPosition(lastDeletedIcon->pos_x, IMG_HEIGHT * 3.0f);
	//std::cout << "Delete: " << lastDeletedIcon->pos_x << ":" << lastDeletedIcon->pos_y << std::endl;
	// hide the iconObj
	iconObject->SetEnabled(false);
	IETThread::sleep(500); // timer for showing the deleted icon(color indicator)

	mutex->release();
	inserterSem->release();
}

void TextureDisplay::ConvertIconsToObjs()
{
	for (int i = 0; i < TOTAL_ICONS; ++i)
	{
		String objectName = "Icon_" + to_string(iconBank.size());
		IconObject* iconObj = new IconObject(objectName, iconBank.size());
		iconObj->SetEnabled(false);
		iconBank.emplace_back(iconObj);
		GameObjectManager::GetInstance()->AddObject(iconObj);
	}
}

void TextureDisplay::DisplaySetIcons()
{
	std::srand(std::time(nullptr));
	for (int i = 0; i < ICONS_DISPLAYED_LIMIT; ++i)
	{
		// get a random icon from the 'displayedIcons' list
		int random_num = std::rand() % iconBank.size();
		IconObject* iconObj = iconBank[random_num];
		// transfer the selected icon to the 'iconBank'
		iconBank.erase(iconBank.begin() + random_num);
		iconBank.shrink_to_fit();
		displayedIcons.emplace_back(iconObj);
		iconObj->SetEnabled(true); // enable the obj
		// set position in the world
		float x = this->columnGrid * IMG_WIDTH;
		float y = this->rowGrid * IMG_HEIGHT;
		iconObj->SetPosition(x, y);

		this->columnGrid++;
		if (this->columnGrid == this->MAX_COLUMN)
		{
			this->columnGrid = 0;
			this->rowGrid++;
		}
	}
}

