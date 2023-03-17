#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
#include "UI/Buttons/ButtonListener.h"

class MainMenuScreen : public AGameObject, public ButtonListener
{
public:
	MainMenuScreen(string name);
	~MainMenuScreen();

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};
