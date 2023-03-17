#include "SceneManager.h"
#include <iostream>

#include "Scene/AScene.h"

String SceneManager::LOADING_SCENE = "LoadScene";
String SceneManager::MAINMENU_SCENE = "MainMenuScene";

SceneManager* SceneManager::sharedInstance = nullptr;

using namespace std;
SceneManager* SceneManager::getInstance()
{
	if (sharedInstance == nullptr) {
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

String SceneManager::CurrentSceneName()
{
	return toLoadSceneName;
}

void SceneManager::loadScene(string name)
{
	isLoading = true;
	toLoadSceneName = name;
	//put a loading screen!

}

void SceneManager::unloadScene()
{
	if (activeScene != nullptr) {
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