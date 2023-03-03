#include "BaseRunner.h"

#include "Components/Renderer/TextureDisplay.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/FontManager.h"
#include "Utilities/Manager/SFXManager.h"
#include "Utilities/Manager/TextureManager.h"
#include "Utilities/Statistics/FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {

	window.setFramerateLimit(60);

	//load initial textures
	TextureManager::GetInstance()->LoadFromAssetList();
	FontManager::GetInstance()->LoadAll();
	SFXManager::getInstance()->LoadAll();

	//load objects
	BGObject* bgObject = new BGObject("BGObject", "Desert");
	GameObjectManager::GetInstance()->AddObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::GetInstance()->AddObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::GetInstance()->AddObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			//Update(TIME_PER_FRAME);
			update(elapsedTime);
		}

		render();
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			this->window.close();
			break;
		default: 
			GameObjectManager::GetInstance()->ProcessInput(event);
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::GetInstance()->Update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::GetInstance()->Draw(&this->window);
	this->window.display();
}