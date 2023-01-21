#include "IconObject.h"

#include "BaseWindow/BaseWindow.h"
#include "Components/Renderer/Renderer.h"
#include "Utilities/TextureManager.h"

IconObject::IconObject(String name, String iconName) : ::AGameObject(name), iconName(iconName)
{
}

void IconObject::Initialize()
{
	AGameObject::Initialize();

	// assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::GetInstance()->GetTexture(iconName));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setTextureRect(sf::IntRect(0, 0, 60, 60));
	GetTransformable()->setPosition(0, 0);

	Renderer* renderer = new Renderer("icon");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}
