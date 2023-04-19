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
	outfile.close();
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
	outfile = std::ofstream("exampleOutput.txt");

	guard = new Mutex();
	condition_delete = new Condition();
	condition_insert = new Condition();
	condition_search = new Condition();

	mutex = new GlobalSemaphore(1, 1);
	isClose = new GlobalSemaphore(1, 1);
	searcherSem = new GlobalSemaphore(MAX_SEARCHER, MAX_SEARCHER);
	deleterSem = new GlobalSemaphore(0, MAX_DELETER);
	inserterSem = new GlobalSemaphore(0, MAX_INSERTER);

	lastDeletedIcon = nullptr;

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
	searcherSem->acquire();
	mutex->acquire();

	// random select an icon from the 'iconBank'
	std::srand(std::time(nullptr));
	int random_num = std::rand() % displayedSearchList.size();

	IconObject* icon_object = displayedSearchList[random_num];
	searchList.emplace_back(icon_object);

	auto it = std::remove(displayedSearchList.begin(), displayedSearchList.end(), icon_object);
	displayedSearchList.erase(it, displayedSearchList.end());
	displayedSearchList.shrink_to_fit();

	green_arrows[ID]->SetPosition(-IMG_WIDTH, IMG_HEIGHT * 1.5f);
	// perform an arrow animation
	while (green_arrows[ID]->GetPosition().x != icon_object->GetPosition().x)
	{
		float x = green_arrows[ID]->GetPosition().x;
		green_arrows[ID]->SetPosition(x + IMG_WIDTH, IMG_HEIGHT * 1.5f);
		IETThread::sleep(50); // timer for showing the deleted icon(color indicator)
	}

	mutex->release();
	isClose->acquire();
	//std::cout << "Random Number(Search): " << random_num << std::endl;
	//std::cout << "Search: " << searchList[0]->GetName() << " " << searchList[0]->GetPosition().x << ":" << searchList[0]->GetPosition().y << std::endl;

	// Use a lambda to remove icon_object from searchList
	auto remove_from_searchList = [&, icon_object]() {
		auto it = std::remove(searchList.begin(), searchList.end(), icon_object);
		searchList.erase(it, searchList.end());
		searchList.shrink_to_fit();
	};

	deleterSem->release();
	remove_from_searchList();
}
void TextureDisplay::TryInsert(int ID)
{
	inserterSem->acquire();
	mutex->acquire();
	// random select an icon from the 'iconBank'
	std::srand(std::time(nullptr));
	int random_num = std::rand() % iconBank.size();

	// transfer the 'new' icon to the 'displayedIcons'
	IconObject* newIcon = iconBank[random_num];
	displayedIcons.emplace_back(newIcon);
	auto it = std::remove(iconBank.begin(), iconBank.end(), newIcon);
	iconBank.erase(it, iconBank.end());
	iconBank.shrink_to_fit();
	// add the new icon to displayed search list
	displayedSearchList.emplace_back(newIcon);
	// transfer the 'lastDeleted' icon to the 'iconBank'
	iconBank.emplace_back(lastDeletedIcon);
	auto it2 = std::remove(displayedIcons.begin(), displayedIcons.end(), lastDeletedIcon);
	displayedIcons.erase(it2, displayedIcons.end());
	displayedIcons.shrink_to_fit();
	// show orange arrow
	for (int i = 0; i < MAX; ++i)
	{
		if (i == ID)
		{
			orange_arrows[ID]->SetPosition(lastDeletedIcon->GetPosition().x, IMG_HEIGHT * (3.0f + 1.5f * (ID + 1) ));
			break;
		}
	}
	// enable and set the position based on the recently deleted icon
	newIcon->SetEnabled(true);
	newIcon->SetPosition(lastDeletedIcon->GetPosition().x, lastDeletedIcon->GetPosition().y);
	if (outfile.is_open()) {  // check if the file was successfully opened
		outfile << "Insert(Name): " << newIcon->GetName() << " Index: " << (int)newIcon->GetPosition().x / 68 << std::endl;
	}
	//std::cout << "Insert: " << newIcon->GetName() << " " << newIcon->GetPosition().x << ":" << newIcon->GetPosition().y << std::endl;

	IETThread::sleep(500); // timer for showing the deleted icon(color indicator)
	mutex->release();
	isClose->release();
	searcherSem->release();
}

void TextureDisplay::TryDelete(int ID)
{
	deleterSem->acquire();
	mutex->acquire();
	
	// get the selected icon to be deleted
	lastDeletedIcon = searchList[0];
	// show red arrow
	red_arrow->SetPosition(lastDeletedIcon->GetPosition().x, IMG_HEIGHT * 3.0f);
	// hide the iconObj
	lastDeletedIcon->SetEnabled(false);
	// delete the recently search icon
	auto it = std::remove(searchList.begin(), searchList.end(), lastDeletedIcon);
	searchList.erase(it, searchList.end());
	searchList.shrink_to_fit();
	if (outfile.is_open()) {  // check if the file was successfully opened
		outfile << "Delete(Name): " << lastDeletedIcon->GetName() << " Index: " << (int)lastDeletedIcon->GetPosition().x / 68 << std::endl;
	}
	//std::cout << "Delete: " << lastDeletedIcon->GetName() << " " << lastDeletedIcon->GetPosition().x << ":" << lastDeletedIcon->GetPosition().y << std::endl;

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
		displayedSearchList.emplace_back(iconObj);
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

IconObject* TextureDisplay::GetObjectFromList(const IconList& list, const IconObject* obj, int& index)
{
	int i = 0;
	for (IconObject* item : list) {
		if (item == obj) {
			return item;
		}
		i++;
		index = i;
	}
	return nullptr;
}

bool TextureDisplay::IsObjectInIconList(const IconList& list, const IconObject* obj)
{
	for (IconObject* item : list) {
		if (item == obj) {
			return true;
		}
	}
	return false;
}

