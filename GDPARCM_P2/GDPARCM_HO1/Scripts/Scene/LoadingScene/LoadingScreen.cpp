#include "LoadingScreen.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/AGameObject.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "UI/Buttons/UIButton.h"
#include "Utilities/Manager/ApplicationManager.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/SFXManager.h"
#include "Utilities/Manager/TextureManager.h"


LoadingScreen::LoadingScreen(string name) : AGameObject(name), ButtonListener()
{
}

LoadingScreen::~LoadingScreen()
{
	AGameObject::~AGameObject();
}

void LoadingScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::GetInstance()->GetFromTextureMap("title2_bg", 0));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);

	float posX = BaseRunner::WINDOW_WIDTH / 2;
	float posY = BaseRunner::WINDOW_HEIGHT / 2;
	this->SetPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

	sf::Texture* btnNormal = TextureManager::GetInstance()->GetFromTextureMap("btn_normal", 0);
	sf::Texture* btnPressed = TextureManager::GetInstance()->GetFromTextureMap("btn_pressed", 0);

	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->AttachChild(button1);
	button1->SetPosition(0, -50);
	button1->GetTransformable()->setScale(0.3f, 0.3f);
	button1->SetButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button1->AttachChild(button_1Text);
	button_1Text->SetPosition(0, 0);
	button_1Text->SetSize(100);
	button_1Text->SetText("START");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->AttachChild(button2);
	button2->SetPosition(0, 50);
	button2->GetTransformable()->setScale(0.3f, 0.3f);
	button2->SetButtonListener(this);
	UIText* button_2Text = new UIText("text_1");
	button2->AttachChild(button_2Text);
	button_2Text->SetPosition(0, 0);
	button_2Text->SetSize(100);
	button_2Text->SetText("EXIT");

	UIButton* button3 = new UIButton("button_3", btnNormal, btnPressed);
	this->AttachChild(button3);
	button3->SetPosition(0, 150);
	button3->GetTransformable()->setScale(0.3f, 0.3f);
	button3->SetButtonListener(this);
	UIText* button_3Text = new UIText("text_1");
	button3->AttachChild(button_3Text);
	button_3Text->SetPosition(0, 0);
	button_3Text->SetSize(50);
	button_3Text->SetText("Instructions");

	SFXManager::getInstance()->PlaySound("MainMenuBG");
	SFXManager::getInstance()->LoopSound("MainMenuBG", true);
	SFXManager::getInstance()->SoundVolume("MainMenuBG", 50);
}

void LoadingScreen::onButtonClick(UIButton* button)
{
}

void LoadingScreen::onButtonReleased(UIButton* button)
{
	if (button->GetName() == "button_1") {
		SceneManager::getInstance()->loadScene(SceneManager::LOADING_SCENE);
		ApplicationManager::GetInstance()->ResumeApplication();
		SFXManager::getInstance()->PauseSound("MainMenuBG");
	}
	/*
	else if (button->getName() == "button_2") {
		QuitScreen* quitScreen = new QuitScreen("QuitScreen");
		quitScreen->markMainMenuQuit();
		GameObjectManager::GetInstance()->addObject(quitScreen);
	}
	else if (button->getName() == "button_3") {
		InstructionsMenu* insScreen = new InstructionsMenu("insScreen");
		insScreen->markMainMenuQuit();
		GameObjectManager::GetInstance()->addObject(insScreen);
	}
	*/
}

