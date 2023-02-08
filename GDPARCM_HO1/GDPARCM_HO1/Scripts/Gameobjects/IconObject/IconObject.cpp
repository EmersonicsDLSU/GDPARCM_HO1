#include "IconObject.h"

#include "BaseWindow/BaseWindow.h"
#include "Components/Renderer/Renderer.h"
#include "Utilities/Manager/TextureManager.h"

IconObject::IconObject(String name, String iconName) : ::AGameObject(name), iconName(iconName)
{
}

void IconObject::Initialize()
{
	AGameObject::Initialize();

	// assign texture
	sprite = new sf::Sprite();
	texture = TextureManager::GetInstance()->GetTexture(iconName);
	if (texture != nullptr)
		sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(0, 0, 60, 60));
	GetTransformable()->setPosition(0, 0);

	// assign a Renderer component for drawing the texture
	Renderer* renderer = new Renderer("icon");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}
