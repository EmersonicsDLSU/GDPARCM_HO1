#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class SFXManager
{
public:
	static SFXManager* getInstance();
	void LoadAll();
	sf::Sound* GetSound(std::string);
	void PlaySound(std::string);
	void PauseSound(std::string);
	void SoundVolume(std::string key, int vol);
	void StopSound(std::string);
	void LoopSound(std::string key, bool loop);


private:
	SFXManager() {};
	SFXManager(SFXManager const&) {};             // copy constructor is private
	SFXManager& operator=(SFXManager const&) {};  // assignment operator is private
	~SFXManager();
	static SFXManager* sharedInstance;

	void LoadAudio(std::string, std::string);
	std::unordered_map<std::string, sf::Sound*> soundMap;
};