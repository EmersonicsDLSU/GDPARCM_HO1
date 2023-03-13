#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class UIText :
	public AGameObject
{
public:
	UIText(String name);
	void Initialize() override;

	void SetText(String text);
	void SetColor(sf::Color color, sf::Color outline);
	String GetText();
	void SetSize(unsigned int size);
private:
	sf::Text* text;
};
