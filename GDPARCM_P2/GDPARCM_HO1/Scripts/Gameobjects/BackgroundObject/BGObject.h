#pragma once
#include "Gameobjects/Utilities/AGameObject.h"

class BGMPlaylist;

class BGObject : public AGameObject
{
	public:
		BGObject(String name, String bgName, String scenePlaylist);
		~BGObject();
		void Initialize() override;
	private:
		const float SPEED_MULTIPLIER = 3000.0f;
		String bgName;
		String scenePlaylist;
		BGMPlaylist* playlist = nullptr;
};

