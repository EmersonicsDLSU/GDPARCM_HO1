#include "BGMPlaylist.h"

#include <SFML/Audio/SoundSource.hpp>

#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/AGameObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "UI/Buttons/UIButton.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/SFXManager.h"
#include "Utilities/Manager/TextureManager.h"

BGMPlaylist::BGMPlaylist(String name, String scenePlaylist) : AComponent(name, Script), scenePlaylist(scenePlaylist)
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
	SFXManager::getInstance()->StopSound(currentSoundPlaying->key);
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
	if (currentSoundPlaying->sound->getStatus() != sf::SoundSource::Playing && !isPaused) 
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

	sf::Texture* frwdNormal = TextureManager::GetInstance()->GetFromTextureMap("forward_button", 0);
	sf::Texture* frwdPressed = TextureManager::GetInstance()->GetFromTextureMap("forward_button", 0);
	sf::Texture* bckNormal = TextureManager::GetInstance()->GetFromTextureMap("back_button", 0);
	sf::Texture* bckPressed = TextureManager::GetInstance()->GetFromTextureMap("back_button", 0);
	sf::Texture* pauseNormal = TextureManager::GetInstance()->GetFromTextureMap("pause_button", 0);
	sf::Texture* pausePressed = TextureManager::GetInstance()->GetFromTextureMap("pause_button", 0);

	forward = new UIButton("forward_btn", frwdNormal, frwdPressed);
	GameObjectManager::GetInstance()->AddObject(forward);

	backward = new UIButton("backward_btn", bckNormal, bckPressed);
	GameObjectManager::GetInstance()->AddObject(backward);

	pause = new UIButton("pause_btn", pauseNormal, pausePressed);
	GameObjectManager::GetInstance()->AddObject(pause);

	if (SceneManager::getInstance()->CurrentSceneName() == SceneManager::LOADING_SCENE)
	{
		forward->SetScale(0.0125f, 0.0125f);
		forward->SetPosition(200, 160);
		forward->SetButtonListener(this);

		backward->SetScale(0.0125f, 0.0125f);
		backward->SetPosition(60, 160);
		backward->SetButtonListener(this);

		pause->SetScale(0.1f, 0.1f);
		pause->SetPosition(130, 160);
		pause->SetButtonListener(this);
	}
	else if (SceneManager::getInstance()->CurrentSceneName() == SceneManager::MAINMENU_SCENE)
	{
		forward->SetScale(0.0125f, 0.0125f);
		forward->SetPosition(BaseRunner::WINDOW_WIDTH / 2 + 70, BaseRunner::WINDOW_WIDTH / 2 + 50);
		forward->SetButtonListener(this);

		backward->SetScale(0.0125f, 0.0125f);
		backward->SetPosition(BaseRunner::WINDOW_WIDTH / 2 - 70, BaseRunner::WINDOW_WIDTH / 2 + 50);
		backward->SetButtonListener(this);

		pause->SetScale(0.1f, 0.1f);
		pause->SetPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_WIDTH / 2 + 50);
		pause->SetButtonListener(this);
	}

}

void BGMPlaylist::ChangeSong(int type)
{
	SFXManager::getInstance()->StopSound(currentSoundPlaying->key);
	if (type == 0)
	{
		if (++currentIndex >= SFXManager::getInstance()->GetBGM_Playlist().size()) currentIndex = 0;
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[currentIndex];
		songText->SetText(currentSoundPlaying->name);
		_isAnimPlaying = true;
		_animTicks = 0;
	}
	else if (type == 1)
	{
		if (--currentIndex < 0) currentIndex = SFXManager::getInstance()->GetBGM_Playlist().size() - 1;
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[currentIndex];
		songText->SetText(currentSoundPlaying->name);
		_isAnimPlaying = true;
		_animTicks = 0;
	}

	SFXManager::getInstance()->PlaySound(currentSoundPlaying->key);
}

void BGMPlaylist::onButtonClick(UIButton* button)
{
}

void BGMPlaylist::onButtonReleased(UIButton* button)
{
	if (button->GetName() == "forward_btn") {
		std::cout << "Forward\n";
		ChangeSong(0);
	}
	else if (button->GetName() == "backward_btn") {
		std::cout << "Backward\n";
		ChangeSong(1);
	}
	else if (button->GetName() == "pause_btn") {
		isPaused = !isPaused;

		sf::Texture* pauseNormal = TextureManager::GetInstance()->GetFromTextureMap("pause_button", 0);
		sf::Texture* pausePressed = TextureManager::GetInstance()->GetFromTextureMap("pause_button", 0);
		sf::Texture* playNormal = TextureManager::GetInstance()->GetFromTextureMap("play_button", 0);
		sf::Texture* playPressed = TextureManager::GetInstance()->GetFromTextureMap("play_button", 0);

		if (!isPaused)
		{
			SFXManager::getInstance()->PlaySound(currentSoundPlaying->key);
			pause->changeTexture(playNormal, playPressed);
		}
		else
		{
			SFXManager::getInstance()->StopSound(currentSoundPlaying->key);
			pause->changeTexture(pauseNormal, pausePressed);
		}
	}
}

void BGMPlaylist::DisplaySongText()
{
	_animTicks += deltaTime.asSeconds();
	
	if (scenePlaylist == SceneManager::LOADING_SCENE && SceneManager::getInstance()->CurrentSceneName() == SceneManager::LOADING_SCENE)
	{
		// If the animation is not yet complete
		if (_animTicks < _animDuration)
		{
			sf::Vector2f startPos = { 135, -100 };
			sf::Vector2f endPos = { 135, 100 };
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
	else if (scenePlaylist == SceneManager::MAINMENU_SCENE && SceneManager::getInstance()->CurrentSceneName() == SceneManager::MAINMENU_SCENE)
	{
		// If the animation is not yet complete
		if (_animTicks < _animDuration)
		{
			// Update the position of the circle
			songText->SetPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_WIDTH / 2);
			songText->SetColor(sf::Color::White, sf::Color::Black);
			// Update the position of the circle
			nowPlayingText->SetPosition(songText->GetPosition().x, songText->GetPosition().y - 50);
		}
		else
		{
			_animTicks = 0;
			_isAnimPlaying = false;
		}
	}
}
