#include "FPSCounter.h"

#include "BaseWindow/BaseWindow.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"

FPSCounter::FPSCounter(String name, String none) : ::AGameObject(name)
{
    // ui text
    button_1Text = new UIText("FPS_COUNTER");
    GameObjectManager::GetInstance()->AddObject(button_1Text);
    button_1Text->SetPosition(BaseWindow::WINDOW_WIDTH - 150,
        BaseWindow::WINDOW_HEIGHT - 70);
    button_1Text->SetSize(25);
}

void FPSCounter::Initialize()
{
	AGameObject::Initialize();
}

void FPSCounter::Update(sf::Time deltaTime)
{
    AGameObject::Update(deltaTime);

    fps = floor(1.0f / deltaTime.asSeconds());
    char str[40];
    sprintf(str, "%.1f", fps);
    string strFPS = str;
    button_1Text->SetText("FPS: " + strFPS);
}

float FPSCounter::GetFPS()
{
    return fps;
}
