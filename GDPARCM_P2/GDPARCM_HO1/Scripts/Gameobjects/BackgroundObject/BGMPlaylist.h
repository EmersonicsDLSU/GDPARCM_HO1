#pragma once
#include "Components/Utilities/AComponent.h"
#include "UI/Buttons/ButtonListener.h"
#include "Utilities/Manager/SFXManager.h"

class UIText;

namespace sf
{
	class Sound;
}

class BGMPlaylist : public AComponent, public ButtonListener
{
public:
	BGMPlaylist(String name);
	~BGMPlaylist();
	void Perform() override;
	void Initialize() override;
	void ChangeSong(int type);

	void onButtonClick(UIButton* button) override;
	void onButtonReleased(UIButton* button) override;
private:
	void DisplaySongText();
private:
	UIText *songText, *nowPlayingText;
	SFX *currentSoundPlaying = nullptr;
	int currentIndex = 0;

	float _animTicks = 0.0f, _animDuration = 5.0f;
	bool _isAnimPlaying = false;

	UIButton *forward = nullptr;
	UIButton *backward = nullptr;
	UIButton *pause = nullptr;
	bool isPaused = false;
};
