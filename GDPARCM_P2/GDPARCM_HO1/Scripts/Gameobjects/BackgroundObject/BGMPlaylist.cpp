#include "BGMPlaylist.h"

#include <SFML/Audio/SoundSource.hpp>

#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/AGameObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "UI/Buttons/UIButton.h"
#include "Utilities/Manager/SFXManager.h"
#include "Utilities/Manager/TextureManager.h"

BGMPlaylist::BGMPlaylist(String name) : AComponent(name, Script)
{
	// ui text
	songText = new UIText("Song_Text");
	GameObjectManager::GetInstance()->AddObject(songText);
	songText->SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		0);
	songText->SetSize(25);
	// ui text
	nowPlayingText = new UIText("NowPlaying");
	GameObjectManager::GetInstance()->AddObject(nowPlayingText);
	nowPlayingText->SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		0);
	nowPlayingText->SetSize(35);
	nowPlayingText->SetText("Now Playing");
}

BGMPlaylist::~BGMPlaylist()
{
}

void BGMPlaylist::Perform()
{
	if (currentSoundPlaying == nullptr)
	{
		int startingBgm = std::rand() % SFXManager::getInstance()->GetBGM_Playlist().size();
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[startingBgm];
		songText->SetText(currentSoundPlaying->name);
		_isAnimPlaying = true;
		currentIndex = startingBgm;
		SFXManager::getInstance()->PlaySound(currentSoundPlaying->key);
	}
	if (currentSoundPlaying->sound->getStatus() != sf::SoundSource::Playing) 
	{
		if (++currentIndex >= SFXManager::getInstance()->GetBGM_Playlist().size()) currentIndex = 0;
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[currentIndex];
		songText->SetText(currentSoundPlaying->name);
		_isAnimPlaying = true;

		SFXManager::getInstance()->PlaySound(currentSoundPlaying->key);
	}

	if (_isAnimPlaying)
		DisplaySongText();

	AComponent::Perform();
}

void BGMPlaylist::Initialize()
{
	AComponent::Initialize();
	

	sf::Texture* btnNormal = TextureManager::GetInstance()->GetFromTextureMap("btn_normal", 0);
	sf::Texture* btnPressed = TextureManager::GetInstance()->GetFromTextureMap("btn_pressed", 0);

	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	GameObjectManager::GetInstance()->AddObject(button1);
	button1->SetScale(0.2f, 0.2f);
	button1->SetPosition( 60, 160);
	button1->SetButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button1->AttachChild(button_1Text);
	button_1Text->SetPosition(0, -50);
	button_1Text->SetSize(100);
	button_1Text->SetText("change");
}

void BGMPlaylist::ChangeSong()
{
	SFXManager::getInstance()->StopSound(currentSoundPlaying->key);

	if (++currentIndex >= SFXManager::getInstance()->GetBGM_Playlist().size()) currentIndex = 0;
	currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[currentIndex];
	songText->SetText(currentSoundPlaying->name);
	_isAnimPlaying = true;

	SFXManager::getInstance()->PlaySound(currentSoundPlaying->key);
}

void BGMPlaylist::onButtonClick(UIButton* button)
{
}

void BGMPlaylist::onButtonReleased(UIButton* button)
{
	if (button->GetName() == "button_1") {
		ChangeSong();
	}
}

void BGMPlaylist::DisplaySongText()
{
	_animTicks += deltaTime.asSeconds();
	// If the animation is not yet complete
	if (_animTicks < _animDuration)
	{
		sf::Vector2f startPos = { BaseRunner::WINDOW_WIDTH / 8, -100 };
		sf::Vector2f endPos = { BaseRunner::WINDOW_WIDTH / 8, 100 };
		// Calculate the current position of the circle
		float x = startPos.x + ((endPos.x - startPos.x) / _animDuration) * _animTicks;
		float y = startPos.y + ((endPos.y - startPos.y) / _animDuration) * _animTicks;

		// Update the position of the circle
		songText->SetPosition(x, y);
		// Update the position of the circle
		nowPlayingText->SetPosition(x, y - 50);
	}
	else
	{
		_animTicks = 0;
		_isAnimPlaying = false;
	}
}
