#pragma once
#include "Utilities/Typedefs.h"

class AGameObject;
// deals with loading of resources, and loading of objects, then registering them to object manager.
// also does the opposite, unloading.
class AScene
{
public:
	AScene(String sceneName);
	~AScene();

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	String getSceneName();

protected:
	void registerObject(AGameObject* object); //IMPORTANT: This must be called for every object to be loaded/unloaded.
	String sceneName;
};