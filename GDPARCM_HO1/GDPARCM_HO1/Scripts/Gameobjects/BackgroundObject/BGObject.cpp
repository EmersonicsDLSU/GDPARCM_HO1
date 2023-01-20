#include "BGObject.h"
#include <string>
#include <iostream>
#include "BGMovement.h"
#include "BaseWindow/BaseWindow.h"
#include "Components/Renderer/Renderer.h"
#include "Utilities/TextureManager.h"

BGObject::BGObject(std::string name, std::string bgName) : ::AGameObject(name), bgName(bgName) {}

void BGObject::Initialize()
{
	AGameObject::Initialize();
	
	// assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::GetInstance()->GetTexture(bgName));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	// make BG height x k to emulate repeating BG.
	sprite->setTextureRect(sf::IntRect(0, 0, BaseWindow::WINDOW_WIDTH, BaseWindow::WINDOW_HEIGHT * 10));
	GetTransformable()->setPosition(0, BaseWindow::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BG_Movement");
	AttachComponent(movement);

	Renderer* renderer = new Renderer("BG");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}
