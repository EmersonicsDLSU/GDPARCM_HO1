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
	//LoadAudio("winsound", "sounds/win.wav");
}


void SFXManager::LoadAudio(std::string key, std::string path) {
	sf::SoundBuffer* sound = new sf::SoundBuffer();
	sf::Sound* audio = new sf::Sound();
	sound->loadFromFile(path);
	audio->setBuffer(*sound);
	soundMap[key] = audio;
}

sf::Sound* SFXManager::GetSound(std::string key) {
	if (soundMap[key] != NULL) {
		return soundMap[key];
	}
	else {
		std::cout << "No Audio found for " << key;
		return NULL;
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
