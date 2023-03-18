#include "MainMenuScene.h"
#include <iostream>
#include "MainMenuScreen.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/HouseSlideShow/DesignSlideShow.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/SFXManager.h"

MainMenuScene::MainMenuScene() : AScene("MainMenuScene")
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onLoadResources()
{

}

void MainMenuScene::onLoadObjects()
{

	//load objects
	BGObject* bgObject = new BGObject("BGObject", "fullMainMenu", SceneManager::MAINMENU_SCENE);
	GameObjectManager::GetInstance()->AddObject(bgObject);

	DesignSlideShow* dss = new DesignSlideShow("DesignSlideShow");
	GameObjectManager::GetInstance()->AddObject(dss);

	MainMenuScreen*loading_screen = new MainMenuScreen("LoadingScreen");
	registerObject(loading_screen);
	
}

void MainMenuScene::onUnloadResources()
{
	AScene::onUnloadObjects();
}