#include "BaseWindow.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/FontManager.h"
#include "Utilities/FPSCounter.h"
#include "Utilities/TextureManager.h"

BaseWindow* BaseWindow::sharedInstance = nullptr;

BaseWindow* BaseWindow::GetInstance() {
    //initialize only when we need it
    if (sharedInstance == nullptr) {
        sharedInstance = new BaseWindow();
    }
    return sharedInstance;
}

BaseWindow::BaseWindow() : mWindow(sf::VideoMode(BaseWindow::WINDOW_WIDTH, BaseWindow::WINDOW_HEIGHT), "Dota2 Skills")
{
    mWindow.setFramerateLimit(60);
    TextureManager::GetInstance()->LoadAll();
    FontManager::GetInstance()->LoadAll();
    // creates objects here
    // bgobject
    BGObject* bgObject = new BGObject("BGObject", "desert_bg");
    GameObjectManager::GetInstance()->AddObject(bgObject);



}

void BaseWindow::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {

        ProcessEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > deltaTime) {
            timeSinceLastUpdate -= deltaTime;
            ProcessEvents();
            FPSCounter::GetInstance()->UpdateFPS(floor(1.0f / deltaTime.asSeconds()));
            Update(deltaTime);
        }
        Render();
    }
}

void BaseWindow::ProcessEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            mWindow.close();
            break;
        default:
            GameObjectManager::GetInstance()->ProcessInput(event);
            break;
        }
    }
}

void BaseWindow::Update(sf::Time)
{
    GameObjectManager::GetInstance()->Update(deltaTime);
}

void BaseWindow::Render()
{
    mWindow.clear();
    GameObjectManager::GetInstance()->Draw(&mWindow);
    mWindow.display();
}
