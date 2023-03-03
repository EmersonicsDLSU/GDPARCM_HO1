#include "FPSCounter.h"
#include <iostream>
//#include "IETThread.h"
#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"


FPSCounter::FPSCounter(): ::AGameObject("FPSCounter")
{
	// ui text
	button_1Text = new UIText("FPS_COUNTER");
	GameObjectManager::GetInstance()->AddObject(button_1Text);
	button_1Text->SetPosition(BaseRunner::WINDOW_WIDTH - 150,
		BaseRunner::WINDOW_HEIGHT - 70);
	button_1Text->SetSize(25);
}

void FPSCounter::Initialize()
{
	AGameObject::Initialize();

}

void FPSCounter::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);

	ticks += deltaTime.asSeconds();
	if (ticks >= ticks_threshold)
	{
		this->updateFPS(deltaTime);
		// reset timer
		ticks = 0.0f;
	}
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	AGameObject::Update(elapsedTime);

	float fps = floor(1.0f / elapsedTime.asSeconds());
	fps = floor(1.0f / elapsedTime.asSeconds());
	char str[40];
	sprintf(str, "%.1f", fps);
	string strFPS = str;
	button_1Text->SetText("FPS: " + strFPS);
}
