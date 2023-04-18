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

	lastDeletedIcon = new ICON_struct{0,0,"name", 0};

	// arrows
	for (int i = 0; i < 4; ++i)
	{
		PNGObject* arrow = new PNGObject("green_icon");
		GameObjectManager::GetInstance()->AddObject(arrow);
		green_arrows.emplace_back(arrow);
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
	while (true)
	{
		std::cout << "Call Delete" << std::endl;
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
	UniqueLock unique_lock(*this->guard);

	while (searchersCount >= MAX_SEARCHER)
	{
		condition_search->wait(unique_lock);
	}
	std::cout << "Search: " << ID << std::endl;
	++searchersCount;
	// critical-section
	std::random_device rd;  // obtain a random seed from hardware
	std::mt19937 eng(rd());  // seed the generator
	uniform_int_distribution<int> distr(0, displayedIcons.size() - 1);  // define the range of possible values
	int random_num;
	bool num_chosen = false;
	while (!num_chosen) {
		random_num = distr(eng);  // generate a random number
		if (std::find(searchList.begin(), searchList.end(), random_num) == searchList.end()) {
			// if the random number is not already in the list, add it and exit the loop
			searchList.emplace_back(random_num);
			num_chosen = true;
		}
	}
	// perform an arrow animation
	for (int i = 0; i < random_num; ++i)
	{
		IETThread::sleep(500); // timer for showing the deleted icon(color indicator)
		// set position in the world
		float x = i * IMG_WIDTH;
		float y = 2 * IMG_HEIGHT;
		green_arrows[ID]->SetPosition(x, y);
	}
	// execute a 'delete' event
	bool prev = canDelete;
	canDelete = true;
	if (!prev)
	{
		condition_delete->notify_one();
	}

	unique_lock.unlock();
}

void TextureDisplay::TryInsert(int ID)
{
	UniqueLock unique_lock(*this->guard);

	// hold the thread
	while (!canInsert)
	{
		condition_insert->wait(unique_lock);
	}
	std::cout << "Insert" << std::endl;
	// random select an icon from the 'iconBank'
	std::srand(std::time(nullptr));
	int random_num = std::rand() % displayedIcons.size();

	// transfer the 'new' icon to the 'displayedIcons'
	IconObject* iconObject = iconBank[random_num];
	displayedIcons.emplace_back(iconObject);
	iconBank.erase(iconBank.begin() + random_num);
	iconBank.shrink_to_fit();
	// transfer the 'lastDeleted' icon to the 'iconBank'
	iconBank.emplace_back(displayedIcons[lastDeletedIcon->index]);
	displayedIcons.erase(displayedIcons.begin() + lastDeletedIcon->index);
	displayedIcons.shrink_to_fit();
	// enable and set the position based on the recently deleted icon
	iconObject->SetEnabled(true);
	iconObject->SetPosition(lastDeletedIcon->pos_x, lastDeletedIcon->pos_y);
	// we can call the delete event again
	canDelete = false;
	// disable the insert event
	canInsert = false;
	--searchersCount;
	condition_search->notify_one();

	unique_lock.unlock();
}

void TextureDisplay::TryDelete(int ID)
{
	UniqueLock unique_lock(*this->guard);
	while (!canDelete)
	{
		condition_delete->wait(unique_lock);
	}
	std::cout << "Delete" << std::endl;
	// get the selected icon to be deleted
	IconObject* iconObject = displayedIcons[searchList[0]];
	lastDeletedIcon->name = iconObject->GetName();
	lastDeletedIcon->pos_x = iconObject->GetPosition().x;
	lastDeletedIcon->pos_y = iconObject->GetPosition().y;
	lastDeletedIcon->index = searchList[0];
	// erase the searched number to the 'search' list
	searchList.erase(searchList.begin() + 0);
	searchList.shrink_to_fit();
	// show red arrow
	red_arrow->SetPosition(IMG_WIDTH * lastDeletedIcon->index, IMG_HEIGHT * 1.5f);
	// hide the iconObj
	//IETThread::sleep(500); // timer for showing the deleted icon(color indicator)
	iconObject->SetEnabled(false);
	// notify one inserter
	canInsert = true;
	condition_insert->notify_one();
	unique_lock.unlock();
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

