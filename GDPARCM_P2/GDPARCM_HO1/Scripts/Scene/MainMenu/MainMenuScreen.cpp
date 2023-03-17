#include "MainMenuScreen.h"
#include "Gameobjects/Utilities/AGameObject.h"
#include "UI/Buttons/UIButton.h"
#include "Utilities/Manager/TextureManager.h"


MainMenuScreen::MainMenuScreen(string name) : AGameObject(name), ButtonListener()
{
}

MainMenuScreen::~MainMenuScreen()
{
	AGameObject::~AGameObject();
}

void MainMenuScreen::initialize()
{

}

void MainMenuScreen::onButtonClick(UIButton* button)
{
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{

}

