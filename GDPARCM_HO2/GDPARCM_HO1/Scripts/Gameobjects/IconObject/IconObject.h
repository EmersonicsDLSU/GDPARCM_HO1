#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class IconObject :    public AGameObject
{
public:
	IconObject(String name, int textureIndex);
	void Initialize() override;
private:
	int textureIndex = 0;
};

