#pragma once
#include "Components/Utilities/AComponent.h"

class BGMovement : public AComponent
{
public:
	BGMovement(String name);
	~BGMovement();
	void Perform() override;
	void Initialize() override;
	void SetBGSpeed(float speed);
	float GetBGSpeed();

private:
	float SPEED_MULTIPLIER = 100.0f;
};
