#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class Animator;

class AnimObject : public AGameObject
{
public:
	AnimObject(String name, std::vector<String> animations);
	void Initialize() override;
	void SetInterval(float interval);
private:
	Animator* anim = nullptr;
	std::vector<String> animations;
};

