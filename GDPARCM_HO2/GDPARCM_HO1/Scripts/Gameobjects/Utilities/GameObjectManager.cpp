#include <stddef.h>
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::GetInstance() {
	if (sharedInstance == NULL) {
		//Initialize
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::FindObjectByName(AGameObject::String name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::GetAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::GetActiveObjectsSize()
{
	return gameObjectList.size();
}

void GameObjectManager::ProcessInput(sf::Event event) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		gameObjectList[i]->ProcessInput(event);
	}
}

void GameObjectManager::Update(sf::Time deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		gameObjectList[i]->Update(deltaTime);
	}
}

//draws the object if it contains a sprite
void GameObjectManager::Draw(sf::RenderWindow* window) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		gameObjectList[i]->Draw(window, sf::RenderStates::Default);
	}
}

void GameObjectManager::AddObject(AGameObject* gameObject)
{
	//also Initialize the oject
	this->gameObjectMap[gameObject->GetName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->GetName()]->Initialize();
	
}

//also frees up allocation of the object.
void GameObjectManager::DeleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->GetName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	
	delete gameObject;
}

void GameObjectManager::DeleteAllObjectsInScene()
{
	vector<AGameObject*>::iterator i;
	for (i = gameObjectList.begin(); i != gameObjectList.end(); i++) {
		delete *i;	
	}

	gameObjectList.clear();
	gameObjectList.shrink_to_fit();
	gameObjectMap.clear();
}

void GameObjectManager::DeleteObjectByName(AGameObject::String name) {
	AGameObject* object = this->FindObjectByName(name);
	
	if (object != NULL) {
		this->DeleteObject(object);
	}
}


GameObjectManager::~GameObjectManager()
{
	DeleteAllObjectsInScene();
	std::cout << "GameObjectManager class deleted\n";
}
