#include "BaseWindow.h"

BaseWindow::BaseWindow() : mWindow(sf::VideoMode(BaseWindow::WINDOW_WIDTH, BaseWindow::WINDOW_HEIGHT), "Dota2 Skills")
{

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

        }
    }
}

void BaseWindow::Update(sf::Time)
{
}

void BaseWindow::Render()
{
    mWindow.clear();
    // TODO: This is where we draw our objects (window.draw(< >))
    mWindow.display();
}
