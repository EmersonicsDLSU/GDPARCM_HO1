#include "BaseRunner.h"

#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Scene/LoadingScene/LoadingScene.h"
#include "Utilities/Manager/ApplicationManager.h"
#include "Utilities/Manager/FontManager.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/SFXManager.h"
#include "Utilities/Manager/TextureManager.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component") {

	window.setFramerateLimit(60);

	//load initial textures
	ApplicationManager::GetInstance()->Initialize(&this->window);
	TextureManager::GetInstance()->LoadFromAssetList();
	FontManager::GetInstance()->LoadAll();
	SFXManager::getInstance()->LoadAll();

	// register scenes
	SceneManager::getInstance()->registerScene(new LoadingScene());

	// load first scene
	SceneManager::getInstance()->loadScene(SceneManager::LOADING_SCENE);
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
		SceneManager::getInstance()->checkLoadScene();
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
	if (!ApplicationManager::GetInstance()->isPaused()) {
		GameObjectManager::GetInstance()->Update(elapsedTime);
		SceneManager::getInstance()->checkLoadScene();
	}
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::GetInstance()->Draw(&this->window);
	this->window.display();
}