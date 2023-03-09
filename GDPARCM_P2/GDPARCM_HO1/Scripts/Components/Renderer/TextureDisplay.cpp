#include "TextureDisplay.h"
#include <iostream>
#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/IconObject/IconObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/TextureManager.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::Initialize()
{
	
}

void TextureDisplay::ProcessInput(sf::Event event)
{
	
}

void TextureDisplay::Update(sf::Time deltaTime)
{
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
	
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
		TextureManager::GetInstance()->SetAssetLoadedCount(++numDisplayed);
	}
}

void TextureDisplay::onFinishedExecution()
{
	// executes spawn once the texture is ready
	spawnObject();

}

void TextureDisplay::spawnObject()
{
	guard.lock();
	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	GameObjectManager::GetInstance()->AddObject(iconObj);
	this->iconList.push_back(iconObj);

	//set position
	float initialWidth = 1600; float initialHeight = 800;

	iconObj->SetScale(initialWidth / iconObj->GetLocalBounds().width,
		initialHeight / iconObj->GetLocalBounds().height);
	//float x = this->columnGrid * IMG_WIDTH;
	//float y = this->rowGrid * IMG_HEIGHT;
	iconObj->SetPosition(100, 100);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	guard.unlock();
}
