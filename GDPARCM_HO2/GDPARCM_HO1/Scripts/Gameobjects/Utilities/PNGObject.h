#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class PNGObject : public AGameObject
{
public:
	PNGObject(String name);
	void Initialize() override;
private:
	int textureIndex = 0;
};

