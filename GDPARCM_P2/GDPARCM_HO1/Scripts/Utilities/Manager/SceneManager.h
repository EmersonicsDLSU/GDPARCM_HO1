#pragma once
#include <unordered_map>

#include "Utilities/Typedefs.h"

class AScene;
typedef std::unordered_map<String, AScene*> SceneTable;
typedef std::vector<String> SceneList;
class SceneManager
{
public:
	//scene names
	static String MAIN_MENU_SCENE_NAME;
	static String GAME_SCENE_NAME;
	static String GAME_SCENE2_NAME;
	static String GAME_SCENE3_NAME;

	static SceneManager* getInstance();
	void registerScene(AScene* scene);
	void loadScene(String name); //also calls unload of the previous scene automatically
	void unloadScene();
	bool isSceneLoaded(String name);
	void checkLoadScene();
	SceneTable storedScenes;

private:
	SceneManager() {};
	SceneManager(SceneManager const&) {};             // copy constructor is private
	SceneManager& operator=(SceneManager const&) {};  // assignment operator is private
	static SceneManager* sharedInstance;

	//SceneTable activeScenes;
	AScene* activeScene;
	String toLoadSceneName;
	bool isLoading = false;

};