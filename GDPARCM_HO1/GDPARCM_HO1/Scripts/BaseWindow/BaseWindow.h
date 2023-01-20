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
    static const int FPS_LIMIT = 60.0f;
    const sf::Time deltaTime = sf::seconds(1.f / 60.f);
public:
    float fps;
private:
    sf::RenderWindow mWindow;
};

