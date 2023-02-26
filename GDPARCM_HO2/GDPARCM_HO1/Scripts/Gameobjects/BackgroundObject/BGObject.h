#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class BGObject : public AGameObject
{
	public:
		BGObject(String name, String bgName);
		void Initialize() override;
	private:
		const float SPEED_MULTIPLIER = 3000.0f;
		String bgName;
};

