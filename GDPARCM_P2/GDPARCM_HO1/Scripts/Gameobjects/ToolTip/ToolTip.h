#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class UIText;

class ToolTip : public AGameObject
{
public:
	ToolTip(String name, std::vector<String> animations);
	void Initialize() override;
	void Update(sf::Time deltaTime) override;

private:
	UIText* button_1Text;
	std::vector<String> toolTipLines;
	int currentToolTipLine = 0;
	float ticks = 0;
	float ticks_threshold = 10.0f;

	void ChangeToolTipLine(sf::Time elapsedTime);

};

