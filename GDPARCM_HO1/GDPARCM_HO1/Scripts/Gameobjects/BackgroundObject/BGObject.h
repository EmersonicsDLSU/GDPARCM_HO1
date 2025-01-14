#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(String name, String bgName);
	void Initialize() override;
private:
	String bgName;
};
