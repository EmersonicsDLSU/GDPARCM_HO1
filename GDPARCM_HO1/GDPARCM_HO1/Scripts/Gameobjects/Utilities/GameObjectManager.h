#pragma once
#include <SFML/System.hpp>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"

class GameObjectManager : sf::NonCopyable
{
public:
    ~GameObjectManager();

    static GameObjectManager* GetInstance();
    AGameObject* FindObjectByName(std::string name);
    std::vector<AGameObject*> GetAllObjects();
    int GetActiveObjectsSize();
    void ProcessInput(sf::Event event);
    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow* window);
    void AddObject(AGameObject* gameObject);
    void DeleteObject(AGameObject* gameObject);
    void DeleteObjectByName(std::string name);
    void DeleteAllObjectsInScene();

private:
    // set constructor to private
    GameObjectManager() {};
    static GameObjectManager* sharedInstance;

    std::unordered_map<std::string, AGameObject*> gameObjectMap;
    std::vector<AGameObject*> gameObjectList;
};