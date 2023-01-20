#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(std::string name, std::string bgName);
	void Initialize() override;
private:
	const float SPEED_MULTIPLIER = 100.0f;
	std::string bgName;
};
