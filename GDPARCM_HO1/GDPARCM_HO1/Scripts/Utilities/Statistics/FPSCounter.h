#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
class UIText;

class FPSCounter : public AGameObject
{
public:
	FPSCounter(String name, String none = "\0");
	void Initialize() override;
	void ProcessInput(sf::Event event) override;
	void Update(sf::Time deltaTime) override;
	void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;
	float GetFPS();
private:
	UIText* button_1Text;
	float fps = 0;
};

