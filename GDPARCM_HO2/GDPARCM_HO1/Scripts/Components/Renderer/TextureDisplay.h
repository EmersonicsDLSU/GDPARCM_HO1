#pragma once
#include <mutex>
#include <set>

#include "Gameobjects/Utilities/AGameObject.h"
#include "Threads/IExecutionEvent.h"

class PNGObject;

namespace std
{
	class mutex;
	class condition_variable;
}

class GlobalSemaphore;
class ThreadPool;
class IconObject;

struct ICON_struct
{
public:
	float pos_x;
	float pos_y;
	std::string name;
	int index;
};

/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay: public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	~TextureDisplay();
	void Initialize();
	void ProcessInput(sf::Event event);
	void Update(sf::Time deltaTime);
	void onFinishedExecution();

	// execution events for S.I.D
	void OnSearch(int ID);
	void OnInsert(int ID);
	void OnDelete(int ID);
	// call functions for execute events
	void CallSearch(int ID);
	void CallInsert(int ID);
	void CallDelete(int ID);
	// Try functions
	void TrySearch(int ID);
	void TryInsert(int ID);
	void TryDelete(int ID);

private:
	// arrow list
	std::vector<PNGObject*> green_arrows;
	std::vector<PNGObject*> orange_arrows;
	PNGObject* red_arrow;
	// Icon list
	typedef std::vector<IconObject*> IconList;
	IconList displayedIcons;
	IconList iconBank; // iconBank for 
	// search list
	std::vector<int> searchList;
	// Thread utilities
	ThreadPool* threadPool;
	// Monitor
	typedef  std::condition_variable Condition;
	typedef  std::mutex Mutex;
	typedef  unique_lock<std::mutex> UniqueLock;
	Condition* condition_delete;
	Condition* condition_insert;
	Condition* condition_search;
	Mutex* guard;
	// Semaphore
	GlobalSemaphore* mutex;
	GlobalSemaphore* deleterSem;
	GlobalSemaphore* inserterSem;
	// variables
	ICON_struct* lastDeletedIcon = nullptr;
	// measure variables
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0;
	int searchersCount = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;
	const int TOTAL_ICONS = 20;
	const int ICONS_DISPLAYED_LIMIT = 10;
	const int MAX_SEARCHER = 4;
	const int MAX_INSERTER = 2;
	const int MAX_DELETER = 1;
	// functions
	void ConvertIconsToObjs();
	void DisplaySetIcons();

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 50;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;
	
};

