#include "AScene.h"

#include "Gameobjects/Utilities/GameObjectManager.h"

AScene::AScene(string sceneName)
{
	this->sceneName = sceneName;
}

AScene::~AScene()
{

}

void AScene::onUnloadObjects()
{
	GameObjectManager::GetInstance()->DeleteAllObjectsInScene();
}

string AScene::getSceneName()
{
	return this->sceneName;
}

void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::GetInstance()->AddObject(object);
}