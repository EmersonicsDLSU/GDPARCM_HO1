#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class IconObject : public AGameObject
{
public:
	IconObject(String name, String iconName);
	void Initialize() override;
private:
	std::string iconName;
};

