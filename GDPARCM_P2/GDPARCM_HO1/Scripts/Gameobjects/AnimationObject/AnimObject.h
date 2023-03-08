#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class AnimObject : public AGameObject
{
public:
	AnimObject(String name, std::vector<String> animations);
	void Initialize() override;
private:
	std::vector<String> animations;
};

