#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class BaseWindow
{
public:
    BaseWindow();
    void Run();
private:
    void ProcessEvents();
    void Update(sf::Time);
    void Render();
public:
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;
    const sf::Time deltaTime = sf::seconds(1.f / 60.f);
private:
    sf::RenderWindow mWindow;
};

