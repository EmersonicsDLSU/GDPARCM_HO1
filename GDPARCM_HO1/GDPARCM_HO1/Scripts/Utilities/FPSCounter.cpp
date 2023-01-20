#include "FPSCounter.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"

FPSCounter* FPSCounter::sharedInstance = nullptr;

FPSCounter* FPSCounter::GetInstance() {
    //initialize only when we need it
    if (sharedInstance == nullptr) {
        sharedInstance = new FPSCounter();
    }
    return sharedInstance;
}

FPSCounter::FPSCounter()
{
    // ui text
    button_1Text = new UIText("FPS_COUNTER");
    GameObjectManager::GetInstance()->AddObject(button_1Text);
    button_1Text->SetPosition(1820, 1030);
    button_1Text->SetSize(25);
}

void FPSCounter::UpdateFPS(float fps)
{
    char str[40];
    sprintf(str, "%.1f", fps);
    sscanf(str, "%f", &fps);
    string strFPS = str;

    button_1Text->SetText("FPS: " + strFPS);
}

float FPSCounter::GetFPS()
{
    return fps;
}
