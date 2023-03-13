#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

enum SFX_Types
{
	BGM = 0,
};
struct SFX
{
	sf::Sound* sound;
	std::string key;
	std::string name;
};

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
	std::vector<SFX*> GetBGM_Playlist();


private:
	SFXManager() {};
	SFXManager(SFXManager const&) {};             // copy constructor is private
	SFXManager& operator=(SFXManager const&) {};  // assignment operator is private
	~SFXManager();
	static SFXManager* sharedInstance;

	void LoadAudio(std::string, std::string, SFX_Types sfxType, std::string name = "\0");
	std::unordered_map<std::string, sf::Sound*> soundMap;
	std::vector<SFX*> soundBGM;
};