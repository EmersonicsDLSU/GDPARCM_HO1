#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the Update function
 */
#include <unordered_map>
#include <vector>
#include <string>
#include "AGameObject.h"
#include <SFML/Graphics.hpp>
#include <mutex>

typedef std::unordered_map<std::string, AGameObject*> HashTable;
typedef std::vector<AGameObject*> List;

class GameObjectManager
{
	public:
		~GameObjectManager();

		static GameObjectManager* GetInstance();
		AGameObject* FindObjectByName(AGameObject::String name);
		List GetAllObjects();
		int GetActiveObjectsSize();
		void ProcessInput(sf::Event event);
		void Update(sf::Time deltaTime);
		void Draw(sf::RenderWindow* window);
		void AddObject(AGameObject* gameObject);
		void DeleteObject(AGameObject* gameObject);
		void DeleteAllObjectsInScene();
		void DeleteObjectByName(AGameObject::String name);

	private:
		GameObjectManager() {};
		GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
		GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private
		static GameObjectManager* sharedInstance;

		HashTable gameObjectMap;
		List gameObjectList;

		typedef std::mutex Mutex;
		Mutex guard;
};

