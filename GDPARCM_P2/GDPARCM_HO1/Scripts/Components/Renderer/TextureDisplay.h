#pragma once
#include <mutex>

#include "Gameobjects/Utilities/AGameObject.h"
#include "Threads/IExecutionEvent.h"

namespace std
{
}

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay: public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void Initialize();
	void ProcessInput(sf::Event event);
	void Update(sf::Time deltaTime);
	void onFinishedExecution();

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 1000;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();

	typedef std::mutex Mutex;
	Mutex guard;
};

