#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
#include "UI/Buttons/ButtonListener.h"

class LoadingScreen : public AGameObject, public ButtonListener
{
public:
	LoadingScreen(string name);
	~LoadingScreen();

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};
