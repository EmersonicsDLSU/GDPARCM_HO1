#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class UIText :
	public AGameObject
{
public:
	UIText(String name);
	~UIText();
	void Initialize() override;

	void SetText(String text);
	String GetText();
	void SetSize(unsigned int size);
private:
	sf::Text* text;
};
