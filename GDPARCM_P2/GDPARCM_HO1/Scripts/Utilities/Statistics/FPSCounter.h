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
		float ticks = 0;
		float ticks_threshold = 0.5f;

		void updateFPS(sf::Time elapsedTime);
		
};

