#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class IconSpawner : public AGameObject
{
public:
	IconSpawner(String name, String none = "\0");
	void Initialize() override;
	void Update(sf::Time deltaTime) override;
private:
	float currentPosX = 0.0f;
	float currentPosY = 0.0f;
	float ticks = 0.0f;
	float spawn_interval = 0.25f;
	float increment = 65.0f;
	int size = 479;
	int index = 0;
	int rowCount = 0;
	int rowLimit = 27;
	int colCount = 0;
	int colLimit = 17;
};

