#pragma once
#include <SFML/Graphics.hpp>

class ApplicationManager
{
public:
	static void Initialize(sf::RenderWindow* window);
	static ApplicationManager* GetInstance();
	void ApplicationQuit();
	void PauseApplication();
	void ResumeApplication();
	bool isPaused();

	enum GameState { Running = 0, Paused = 1 };

private:
	ApplicationManager() {};
	ApplicationManager(ApplicationManager const&) {};             // copy constructor is private
	ApplicationManager& operator=(ApplicationManager const&) {};  // assignment operator is private
	~ApplicationManager();
	static ApplicationManager* sharedInstance;

	sf::RenderWindow* window;
	GameState state;
};