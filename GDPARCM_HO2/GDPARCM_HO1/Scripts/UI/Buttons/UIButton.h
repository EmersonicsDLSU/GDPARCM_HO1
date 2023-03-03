#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class ButtonListener;

class UIButton : public AGameObject
{
public:
	UIButton(String name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	~UIButton();
	void initialize();
	void changeButtonToNormal();
	void changeButtonToPressed();
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void SetButtonListener(ButtonListener* listener);
private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	sf::Sprite* sprite;
	ButtonListener* listener;
};
