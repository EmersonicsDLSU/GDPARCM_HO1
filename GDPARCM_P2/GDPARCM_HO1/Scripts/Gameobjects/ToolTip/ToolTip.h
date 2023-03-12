#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class UIText;

class ToolTip : public AGameObject
{
public:
	ToolTip(String name, std::vector<String> animations);
	void Initialize_Images(std::vector<String> correspondingImages_name);
	void Initialize() override;
	void Update(sf::Time deltaTime) override;

private:
	UIText* button_1Text;
	std::vector<String> toolTipLines;
	std::vector<sf::Texture*> correspondingImages;
	int random_number = 0;
	float ticks = 0;
	float ticks_threshold = 7.0f;

	void ChangeToolTipLine(sf::Time elapsedTime);

};

