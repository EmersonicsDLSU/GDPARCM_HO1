#include "TextureDisplay.h"
#include <iostream>
#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/IconObject/IconObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
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

	TextureManager::GetInstance()->LoadStreamingAssets();
	ConvertIconsToObjs();
	DisplaySetIcons();

	threadPool = new ThreadPool("SID_ThreadPool", 10);
	threadPool->StartScheduler();

	// run threads for 'deleter'
	for (int i = 0; i < MAX_DELETER; ++i)
	{
		CallDelete();
	}
	// run threads for 'inserter'
	for (int i = 0; i < MAX_INSERTER; ++i)
	{
		CallInsert();
	}
	// run threads for 'searcher'
	for (int i = 0; i < MAX_SEARCHER; ++i)
	{
		CallSearch();
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

void TextureDisplay::OnSearch()
{
	while (true)
	{
		TrySearch();
	}
}

void TextureDisplay::OnInsert()
{
	while (true)
	{
		TryInsert();
	}
}


void TextureDisplay::OnDelete()
{
	while (true)
	{
		std::cout << "Call Delete" << std::endl;
		TryDelete();
	}
}

void TextureDisplay::CallSearch()
{
	ThreadLoader* iconSearcher = new ThreadLoader(SID_ENUM::SEARCH, this);
	threadPool->ScheduleTask(iconSearcher);
}

void TextureDisplay::CallInsert()
{
	ThreadLoader* iconInserter = new ThreadLoader(SID_ENUM::INSERT, this);
	threadPool->ScheduleTask(iconInserter);
}

void TextureDisplay::CallDelete()
{
	ThreadLoader* iconDeleter = new ThreadLoader(SID_ENUM::DELETE, this);
	threadPool->ScheduleTask(iconDeleter);
}

void TextureDisplay::TrySearch()
{
	UniqueLock unique_lock(*this->guard);

	while (searchersCount >= MAX_SEARCHER)
	{
		condition_search->wait(unique_lock);
	}
	std::cout << "Search" << std::endl;
	++searchersCount;
	// critical-section
	std::srand(std::time(nullptr));
	// get a random icon from the 'displayedIcons' list
	int random_num = std::rand() % displayedIcons.size();
	searchList.emplace_back(random_num);
	// execute a 'delete' event
	bool prev = canDelete;
	canDelete = true;
	if (!prev)
	{
		condition_delete->notify_one();
	}

	unique_lock.unlock();
}

void TextureDisplay::TryInsert()
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

void TextureDisplay::TryDelete()
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
	// hide the iconObj
	IETThread::sleep(500); // timer for showing the deleted icon(color indicator)
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
		int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
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

