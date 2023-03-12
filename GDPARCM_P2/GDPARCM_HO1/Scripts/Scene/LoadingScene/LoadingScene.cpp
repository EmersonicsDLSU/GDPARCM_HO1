#include "LoadingScene.h"
#include <iostream>

#include "LoadingScreen.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Gameobjects/AnimationObject/AnimObject.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/ProgressBar/ProgressBar.h"
#include "Gameobjects/ToolTip/ToolTip.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/SFXManager.h"
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
	simsIcon->SetScale(56 / simsIcon->GetLocalBounds().width,
		118 / simsIcon->GetLocalBounds().height);

	ProgressBar* progressBar = new ProgressBar("Progress Bar", "progressBar_unfilled", "progressBar_filler", simsIcon);
	GameObjectManager::GetInstance()->AddObject(progressBar);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::GetInstance()->AddObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::GetInstance()->AddObject(fpsCounter);

	ToolTip* toolTip = new ToolTip("ToolTip", 
		{"When running a business, make sure to hire employees and train them well to increase customer satisfaction and profits.",
			"As a detective, make sure to take notes and gather evidence carefully to solve cases faster.",
			"When working as a doctor, try to specialize in a certain area to improve your skills and get promoted faster.",
			"Explore the new world of Magnolia Promenade to discover new shops and items for your Sims."
		}
	);
	GameObjectManager::GetInstance()->AddObject(toolTip);

	/*
	LoadingScreen *loading_screen = new LoadingScreen("LoadingScreen");
	registerObject(loading_screen);
	*/
}

void LoadingScene::onUnloadResources()
{
	AScene::onUnloadObjects();
}