#include "LoadingScene.h"
#include <iostream>

#include "LoadingScreen.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Gameobjects/AnimationObject/AnimObject.h"
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

	AnimObject* simsIcon = new AnimObject("simsIcon", {"simsIcon_0","simsIcon_1",
	"simsIcon_2", "simsIcon_3", "simsIcon_4", "simsIcon_5", "simsIcon_6", "simsIcon_7",
	"simsIcon_8", "simsIcon_9", "simsIcon_10", "simsIcon_11", "simsIcon_12", "simsIcon_13",
	"simsIcon_14", "simsIcon_15"});
	GameObjectManager::GetInstance()->AddObject(simsIcon);
	simsIcon->SetPosition(BaseRunner::WINDOW_WIDTH / 2 - 55,
		BaseRunner::WINDOW_HEIGHT - 200);
	simsIcon->SetScale(56 / simsIcon->GetLocalBounds().width,
		118 / simsIcon->GetLocalBounds().height);

	//TextureDisplay* display = new TextureDisplay();
	//GameObjectManager::GetInstance()->AddObject(display);

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