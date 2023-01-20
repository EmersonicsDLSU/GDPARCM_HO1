#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(std::string name, std::string bgName);
	void Initialize() override;
private:
	std::string bgName;
};
