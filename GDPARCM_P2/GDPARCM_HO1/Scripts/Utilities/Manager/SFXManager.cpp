#include "SFXManager.h"
#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance() {
	//initialize only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}
	return sharedInstance;
}

void SFXManager::LoadAll()
{
	LoadAudio("BaseGame", "../GDPARCM_HO1/Media/Sounds/BaseGame.wav", SFX_Types::BGM);
	LoadAudio("CottageLiving", "../GDPARCM_HO1/Media/Sounds/CottageLiving.wav", SFX_Types::BGM);
	LoadAudio("EcoLifestyle", "../GDPARCM_HO1/Media/Sounds/EcoLifestyle.wav", SFX_Types::BGM);
	LoadAudio("IslandLiving", "../GDPARCM_HO1/Media/Sounds/IslandLiving.wav", SFX_Types::BGM);
	LoadAudio("Seasons", "../GDPARCM_HO1/Media/Sounds/Seasons.wav", SFX_Types::BGM);
	LoadAudio("SnowyEscape", "../GDPARCM_HO1/Media/Sounds/SnowyEscape.wav", SFX_Types::BGM);
}


SFXManager::~SFXManager()
{

}

void SFXManager::LoadAudio(std::string key, std::string path, SFX_Types sfxType) {
	sf::SoundBuffer* sound = new sf::SoundBuffer();
	sf::Sound* audio = new sf::Sound();
	sound->loadFromFile(path);
	audio->setBuffer(*sound);
	soundMap[key] = audio;

	SFX* sfx = new SFX();
	sfx->sound = audio;
	sfx->name = key;

	if (sfxType == SFX_Types::BGM)
		soundBGM.push_back(sfx);
}

sf::Sound* SFXManager::GetSound(std::string key) {
	if (soundMap[key] != nullptr) {
		return soundMap[key];
	}
	else {
		std::cout << "No Audio found for " << key;
		return nullptr;
	}
}

void SFXManager::PlaySound(std::string key)
{
	SFXManager::getInstance()->GetSound(key)->play();
	SFXManager::getInstance()->SoundVolume(key, 40); // default volume = 40
}

void SFXManager::PauseSound(std::string key)
{
	SFXManager::getInstance()->GetSound(key)->pause();
}

void SFXManager::StopSound(std::string key)
{
	SFXManager::getInstance()->GetSound(key)->stop();
}

void SFXManager::SoundVolume(std::string key, int vol)
{
	SFXManager::getInstance()->GetSound(key)->setVolume(vol);
}

void SFXManager::LoopSound(std::string key, bool loop)
{
	SFXManager::getInstance()->GetSound(key)->setLoop(loop);
}

std::vector<SFX*> SFXManager::GetBGM_Playlist()
{
	return soundBGM;
}
