#include "SceneManager.h"
#include <iostream>

#include "Scene/AScene.h"

String SceneManager::MAIN_MENU_SCENE_NAME = "MainMenuScene";
String SceneManager::GAME_SCENE_NAME = "GameScene";
String SceneManager::GAME_SCENE2_NAME = "GameScene2";
String SceneManager::GAME_SCENE3_NAME = "GameScene3";

SceneManager* SceneManager::sharedInstance = NULL;

using namespace std;
SceneManager* SceneManager::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new SceneManager();
	}

	return sharedInstance;
}

void SceneManager::registerScene(AScene* scene)
{
	std::cout << scene->getSceneName() << " registered! \n";
	storedScenes[scene->getSceneName()] = scene;
}


void SceneManager::checkLoadScene() {
	if (isLoading) {
		unloadScene();
		activeScene = storedScenes[this->toLoadSceneName];
		activeScene->onLoadResources();
		activeScene->onLoadObjects();
		isLoading = false;
	}
}

void SceneManager::loadScene(string name)
{
	isLoading = true;
	toLoadSceneName = name;
	//put a loading screen!

}

void SceneManager::unloadScene()
{
	if (activeScene != NULL) {
		cout << "HELLO" << endl;
		activeScene->onUnloadObjects();
		activeScene->onUnloadResources();
	}
}

bool SceneManager::isSceneLoaded(string name)
{
	return activeScene->getSceneName() == name;
}


/*void SceneManager::unloadAllActiveScenes()
{
	SceneList activeList;
	activeList.reserve(this->activeScenes.size());
	for (auto kv : this->activeScenes) {
		activeList.push_back(kv.first);
	}
	for (int i = 0; i < activeList.size(); i++) {
		this->unloadScene(activeList[i]);
	}
}*/