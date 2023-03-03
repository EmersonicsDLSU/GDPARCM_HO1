#include "LoadingScene.h"
#include <iostream>

#include "LoadingScreen.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Statistics/FPSCounter.h"

LoadingScene::LoadingScene() : AScene("LoadScene")
{

}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::onLoadResources()
{

}

void LoadingScene::onLoadObjects()
{
	std::cout << "Main menu scene initialized! \n";

	//load objects
	BGObject* bgObject = new BGObject("BGObject", "Desert");
	GameObjectManager::GetInstance()->AddObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::GetInstance()->AddObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::GetInstance()->AddObject(fpsCounter);

	/*
	LoadingScreen *loading_screen = new LoadingScreen("LoadingScreen");
	registerObject(loading_screen);
	*/
}

void LoadingScene::onUnloadResources()
{
	AScene::onUnloadObjects();
}