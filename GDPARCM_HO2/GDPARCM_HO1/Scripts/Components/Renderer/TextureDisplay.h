#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
#include "Threads/IExecutionEvent.h"

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
	IconList unavailable;
	IconList available;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 50;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;
	const int TOTAL_ICONS = 480;
	const int ICONS_DISPLAYED_LIMIT = 100;

	void ConvertIconsToObjs();
	void DisplaySetIcons();
	void spawnObject();
};

