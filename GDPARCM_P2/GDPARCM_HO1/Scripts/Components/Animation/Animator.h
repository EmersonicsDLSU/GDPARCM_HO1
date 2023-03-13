#pragma once
#include "Components/Utilities/AComponent.h"

class Animator : public AComponent
{
public:
	Animator(String name, std::vector<String> animations);
	~Animator();
	void Perform() override;
	void Initialize() override;
	void SetInterval(float interval);
private:
	std::vector <sf::Texture*> animations;
	int currentAnim = 0;
	float ticks = 0, _animInterval = 0.1f;
};
