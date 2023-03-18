#include "DesignSlideShow.h"
#include <iostream>
//#include "IETThread.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/TextureManager.h"
#include "UI/Buttons/UIButton.h"


DesignSlideShow::DesignSlideShow(String name) : ::AGameObject(name)
{
}

void DesignSlideShow::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";

	// assign texture
	this->sprite = new sf::Sprite();
	String iconName = std::format("tile{:03}", currentImage);
	sprite->setTexture(*TextureManager::GetInstance()->GetFromTextureMap(iconName, 0));

	//set position
	SetScale(680 / GetLocalBounds().width,
		450 / GetLocalBounds().height);
	SetPosition(360, 295);

	Renderer* renderer = new Renderer("ToolTip");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);

	sf::Texture* frwdNormal = TextureManager::GetInstance()->GetFromTextureMap("forward_button", 0);
	sf::Texture* frwdPressed = TextureManager::GetInstance()->GetFromTextureMap("forward_button", 0);
	sf::Texture* bckNormal = TextureManager::GetInstance()->GetFromTextureMap("back_button", 0);
	sf::Texture* bckPressed = TextureManager::GetInstance()->GetFromTextureMap("back_button", 0);

	forward = new UIButton("forward_btn", frwdNormal, frwdPressed);
	GameObjectManager::GetInstance()->AddObject(forward);

	backward = new UIButton("backward_btn", bckNormal, bckPressed);
	GameObjectManager::GetInstance()->AddObject(backward);

	forward->SetScale(0.0125f, 0.0125f);
	forward->SetPosition(450, 500);
	forward->SetButtonListener(this);

	backward->SetScale(0.0125f, 0.0125f);
	backward->SetPosition(310, 500);
	backward->SetButtonListener(this);
	
}

void DesignSlideShow::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);


}

void DesignSlideShow::onButtonClick(UIButton* button)
{
}

void DesignSlideShow::onButtonReleased(UIButton* button)
{
	if (button->GetName() == "forward_btn") {

		if (++currentImage >= totalImage) currentImage = totalImage - 1;
		String iconName = std::format("tile{:03}", currentImage);
		sprite->setTexture(*TextureManager::GetInstance()->GetFromTextureMap(iconName, 0));

	}
	else if (button->GetName() == "backward_btn") {
		if (--currentImage < 0) currentImage = 0;
		String iconName = std::format("tile{:03}", currentImage);
		sprite->setTexture(*TextureManager::GetInstance()->GetFromTextureMap(iconName, 0));
	}
}

