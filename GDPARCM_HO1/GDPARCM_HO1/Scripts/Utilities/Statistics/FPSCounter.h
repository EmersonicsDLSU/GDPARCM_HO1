#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
class UIText;

class FPSCounter : public AGameObject
{
public:
	FPSCounter(String name, String none = "\0");
	void Initialize() override;
	void Update(sf::Time deltaTime) override;
	float GetFPS();
private:
	UIText* button_1Text;
	float fps = 0;
};

