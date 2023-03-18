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
#include "Utilities/Manager/SceneManager.h"
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
	BGObject* bgObject = new BGObject("BGObject", "Blue_BG", SceneManager::LOADING_SCENE);
	GameObjectManager::GetInstance()->AddObject(bgObject);

	ToolTip* toolTip = new ToolTip("ToolTip",
		{ "When running a business, make sure to hire employees and train them well to increase customer satisfaction and profits.",
			"As a detective, make sure to take notes and gather evidence carefully to solve cases faster.",
			"When working as a doctor, try to specialize in a certain area to improve your skills and get promoted faster.",
			"Explore the new world of Magnolia Promenade to discover new shops and items for your Sims.",
			"Join and create clubs to meet new Sims and participate in group activities.",
			"Use the DJ booth to become a DJ and throw your own parties.",
			"Use the new skills, such as Dancing and DJ Mixing, to improve your Sim's abilities and gain more social interactions.",
			"Explore the new world of Windenburg to discover new venues and hidden areas.",
			"Living in an apartment can be challenging, so make sure to pay attention to the neighbors' complaints and maintain a good relationship with them.",
			"Participate in festivals to gain new skills, meet new Sims, and get exclusive items.",
			"Use the new interactions, such as Karaoke and Basketball, to improve your Sim's mood and social interactions.",
			"Explore the new world of San Myshuno to discover new food, music, and cultures.",
			"Owning a pet requires a lot of attention and care, so make sure to feed them, play with them, and take them for walks regularly.",
			"Open a veterinary clinic to treat other Sims' pets and gain profits.",
			"Use the new interactions, such as Pet Training and Pet Grooming, to improve your Sim's relationship with their pets.",
			"Explore the new world of Brindleton Bay to discover new pet-related activities and items.",
			"Weather can affect your Sim's mood and activities, so make sure to dress accordingly and prepare for storms or heatwaves.",
			"Participate in holidays to gain new items, decorations, and activities.",
			"Gardening is a great way to earn money and decorate your home with fresh produce and flowers.",
			"Use the new interactions, such as Ice Skating and Water Balloon fights, to have fun with your Sims during different seasons.",
			"Gaining fame requires a lot of hard work and networking, so make sure to attend events and promote your Sim's skills.",
			"Use the new interactions, such as Acting and Media Production, to improve your Sim's fame and earn money.",
			"Explore the new world of Del Sol Valley to discover new celebrity hotspots and luxury items.",
			"Be careful of the paparazzi and negative publicity, as it can harm your Sim's reputation.",
			"Living on an island requires a lot of water activities and island traditions, so make sure to participate in them regularly."
		}
	);
	toolTip->Initialize_Images({ "toolTip_0", "toolTip_1", "toolTip_2", "toolTip_3", "toolTip_4", "toolTip_5",
	"toolTip_6", "toolTip_7", "toolTip_8", "toolTip_9", "toolTip_10", "toolTip_11",
	"toolTip_12", "toolTip_13", "toolTip_14", "toolTip_15", "toolTip_16", "toolTip_17",
	"toolTip_18", "toolTip_19", "toolTip_20", "toolTip_21", "toolTip_22", "toolTip_23", "toolTip_24" });
	GameObjectManager::GetInstance()->AddObject(toolTip);

	AnimObject* simsIcon = new AnimObject("simsIcon", {"simsIcon_0","simsIcon_1",
	"simsIcon_2", "simsIcon_3", "simsIcon_4", "simsIcon_5", "simsIcon_6", "simsIcon_7",
	"simsIcon_8", "simsIcon_9", "simsIcon_10", "simsIcon_11", "simsIcon_12", "simsIcon_13",
	"simsIcon_14", "simsIcon_15"});
	GameObjectManager::GetInstance()->AddObject(simsIcon);
	simsIcon->SetInterval(0.1f);
	simsIcon->SetScale(56 / simsIcon->GetLocalBounds().width,
		118 / simsIcon->GetLocalBounds().height);

	ProgressBar* progressBar = new ProgressBar("Progress Bar", "progressBar_unfilled", "progressBar_filler", simsIcon);
	GameObjectManager::GetInstance()->AddObject(progressBar);

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