#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::sharedInstance = nullptr;

void ApplicationManager::Initialize(sf::RenderWindow* window)
{
	sharedInstance = new ApplicationManager();
	sharedInstance->window = window;
	sharedInstance->state = Running;
}

ApplicationManager* ApplicationManager::GetInstance()
{
	return sharedInstance;
}

void ApplicationManager::ApplicationQuit()
{
	this->window->close();
}

void ApplicationManager::PauseApplication()
{
	this->state = Paused;
}

void ApplicationManager::ResumeApplication()
{
	this->state = Running;
}

bool ApplicationManager::isPaused()
{
	return this->state == Paused;
}


ApplicationManager::~ApplicationManager()
{

}