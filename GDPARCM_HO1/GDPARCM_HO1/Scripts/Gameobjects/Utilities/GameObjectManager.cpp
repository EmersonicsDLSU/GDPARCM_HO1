#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::GetInstance()
{
	if (sharedInstance == nullptr) {
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::FindObjectByName(std::string name)
{
	if (gameObjectMap[name] != nullptr) {
		return gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return nullptr;
	}
}

std::vector<AGameObject*> GameObjectManager::GetAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::GetActiveObjectsSize()
{
	return gameObjectList.size();
}

void GameObjectManager::ProcessInput(sf::Event event)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->ProcessInput(event);
	}
}

void GameObjectManager::Update(sf::Time deltaTime)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->Update(deltaTime);
	}
}

void GameObjectManager::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->Draw(window, sf::RenderStates::Default);
	}
}

void GameObjectManager::AddObject(AGameObject* gameObject)
{
	gameObjectMap[gameObject->GetName()] = gameObject;
	gameObjectList.push_back(gameObject);
	gameObject->Initialize();
}

void GameObjectManager::DeleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->GetName();
	delete gameObject;
	gameObjectMap.erase(key);
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject), gameObjectList.end());
	gameObjectList.shrink_to_fit();
}

void GameObjectManager::DeleteObjectByName(std::string name)
{
	AGameObject* object = FindObjectByName(name);

	if (object != NULL) {
		DeleteObject(object);
	}
}

void GameObjectManager::DeleteAllObjectsInScene()
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		delete gameObjectList[i];
	}

	gameObjectList.clear();
	gameObjectList.shrink_to_fit();
	gameObjectMap.clear();
}
