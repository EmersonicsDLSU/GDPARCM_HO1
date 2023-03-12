#include "BGMPlaylist.h"

#include <SFML/Audio/SoundSource.hpp>

#include "Gameobjects/Utilities/AGameObject.h"
#include "Utilities/Manager/SFXManager.h"

BGMPlaylist::BGMPlaylist(String name) : AComponent(name, Script)
{
}

BGMPlaylist::~BGMPlaylist()
{
}

void BGMPlaylist::Perform()
{
	if (currentSoundPlaying == nullptr)
	{
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[0];
		currentIndex = 0;

		SFXManager::getInstance()->PlaySound(currentSoundPlaying->name);
	}
	if (currentSoundPlaying->sound->getStatus() != sf::SoundSource::Playing) 
	{
		if (++currentIndex >= SFXManager::getInstance()->GetBGM_Playlist().size()) currentIndex = 0;
		currentSoundPlaying = SFXManager::getInstance()->GetBGM_Playlist()[currentIndex];

		SFXManager::getInstance()->PlaySound(currentSoundPlaying->name);
	}
	AComponent::Perform();
}

void BGMPlaylist::Initialize()
{
	AComponent::Initialize();
}
