#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class ProgressBar : public AGameObject
{
public:
	ProgressBar(String name, String pbName, String fillerName, AGameObject* icon);
	void Initialize() override;
	void Update(sf::Time deltaTime) override;
private:
	float currentProgress = 0;
	float maxFillerWidth;
	String pbName, fillerName;
	AGameObject *icon, *fillerObj;
};

