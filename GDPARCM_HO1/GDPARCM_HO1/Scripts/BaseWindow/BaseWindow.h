#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Utilities/Threads/AppThread.h"

class BaseWindow : public AppThread
{
public:
    static BaseWindow* GetInstance();
    BaseWindow();
    ~BaseWindow();
    void Run();
    // AppThread
    void run() override;
private:
    void ProcessEvents();
    void Update(sf::Time);
    void Render();
public:
    static const sf::Time	TIME_PER_FRAME;
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;
    static const int FPS_LIMIT = 60.0f;
private:
    static BaseWindow* sharedInstance;
    sf::RenderWindow mWindow;
};

