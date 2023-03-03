#include "LoadingScene.h"
#include <iostream>

#include "LoadingScreen.h"

LoadingScene::LoadingScene() : AScene("MainMenuScene")
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
	LoadingScreen *loading_screen = new LoadingScreen("LoadingScreen");
	registerObject(loading_screen);
}

void LoadingScene::onUnloadResources()
{
	AScene::onUnloadObjects();
}