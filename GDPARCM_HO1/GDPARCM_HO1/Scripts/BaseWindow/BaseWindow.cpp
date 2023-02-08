#include "BaseWindow.h"
#include "Gameobjects/BackgroundObject/BGObject.h"
#include "Gameobjects/IconObject/IconSpawner.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/FontManager.h"
#include "Utilities/Manager/TextureManager.h"
#include "Utilities/Statistics/FPSCounter.h"

BaseWindow* BaseWindow::sharedInstance = nullptr;
const sf::Time BaseWindow::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseWindow* BaseWindow::GetInstance() {
    //initialize only when we need it
    if (sharedInstance == nullptr) {
        sharedInstance = new BaseWindow();
    }
    return sharedInstance;
}

BaseWindow::BaseWindow() : mWindow(sf::VideoMode(BaseWindow::WINDOW_WIDTH, BaseWindow::WINDOW_HEIGHT), "Dota2 Skills")
{
    mWindow.setFramerateLimit(FPS_LIMIT);
    TextureManager::GetInstance()->LoadAll();
    FontManager::GetInstance()->LoadAll();

    // creates objects here
    // bgobject
    BGObject* bg_object = new BGObject("BGObject", "desert_bg");
    GameObjectManager::GetInstance()->AddObject(bg_object);
    FPSCounter* fps_Counter = new FPSCounter("FPSCounter");
    GameObjectManager::GetInstance()->AddObject(fps_Counter);
    IconSpawner* icon_spawner = new IconSpawner("IconSpawner");
    GameObjectManager::GetInstance()->AddObject(icon_spawner);

}

BaseWindow::~BaseWindow()
{
    delete GameObjectManager::GetInstance();
    std::cout << "BaseWindow class deleted\n";
}

void BaseWindow::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {

        ProcessEvents();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            ProcessEvents();
            Update(elapsedTime);
        }
        Render();

        // 1 second delay
        sleep(100);
    }
}

void BaseWindow::run()
{
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

void BaseWindow::Update(sf::Time deltaTime)
{
    GameObjectManager::GetInstance()->Update(deltaTime);
}

void BaseWindow::Render()
{
    mWindow.clear();
    GameObjectManager::GetInstance()->Draw(&mWindow);
    mWindow.display();
}
