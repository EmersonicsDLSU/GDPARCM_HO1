#include "ToolTip.h"
#include <iostream>
//#include "IETThread.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/TextureManager.h"


ToolTip::ToolTip(String name, std::vector<String> toolTipLines) : ::AGameObject(name), toolTipLines(toolTipLines)
{
}

void ToolTip::Initialize_Images(std::vector<String> correspondingImages_name)
{
	for (auto path : correspondingImages_name)
	{
		sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(path, 0);
		correspondingImages.push_back(texture);
	}
}

void ToolTip::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";

	// assign texture
	this->sprite = new sf::Sprite();
	sprite->setTexture(*correspondingImages[0]);

	//set position
	SetPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

	Renderer* renderer = new Renderer("ToolTip");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);

	// ui text
	button_1Text = new UIText("toolTip");
	GameObjectManager::GetInstance()->AddObject(button_1Text);
	button_1Text->SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		BaseRunner::WINDOW_HEIGHT - 50);
	button_1Text->SetSize(25);
}

void ToolTip::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);

	ticks += deltaTime.asSeconds();
	if (ticks >= ticks_threshold)
	{
		this->ChangeToolTipLine(deltaTime);
		// reset timer
		ticks = 0.0f;
	}
}

void ToolTip::ChangeToolTipLine(sf::Time elapsedTime)
{
	int new_number = std::rand() % toolTipLines.size();
	while (random_number == new_number)
	{
		new_number = std::rand() % toolTipLines.size();
	}
	random_number = new_number;

	button_1Text->SetText(toolTipLines[random_number]);

	sprite->setTexture(*correspondingImages[random_number]);
}
