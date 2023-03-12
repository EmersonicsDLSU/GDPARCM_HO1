#pragma once
#include "Components/Utilities/AComponent.h"
#include "Utilities/Manager/SFXManager.h"

namespace sf
{
	class Sound;
}

class BGMPlaylist : public AComponent
{
public:
	BGMPlaylist(String name);
	~BGMPlaylist();
	void Perform() override;
	void Initialize() override;

private:
	SFX* currentSoundPlaying = nullptr;
	int currentIndex = 0;
};
