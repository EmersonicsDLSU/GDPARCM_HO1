#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class UIText;

class FPSCounter :    public AGameObject
{
	public:
		FPSCounter();
		void Initialize() override;
		void Update(sf::Time deltaTime) override;
	
	private:
		UIText* button_1Text;
		sf::Time updateTime;;
		int framesPassed = 0;

		void updateFPS(sf::Time elapsedTime);
		
};

