#pragma once
#include "Gameobjects/Utilities/AGameObject.h"
#include "UI/Buttons/ButtonListener.h"


class DesignSlideShow : public AGameObject, public ButtonListener
{
public:
	DesignSlideShow(String name);
	void Initialize() override;
	void Update(sf::Time deltaTime) override;

	void onButtonClick(UIButton* button) override;
	void onButtonReleased(UIButton* button) override;
private:
	int currentImage = 0;
	int totalImage = 116;

	UIButton* forward = nullptr;
	UIButton* backward = nullptr;

};

