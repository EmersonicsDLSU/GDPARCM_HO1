#include "BGObject.h"
#include <string>
#include "BGMovement.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Utilities/Manager/TextureManager.h"

BGObject::BGObject(String name, String bgName) : ::AGameObject(name), bgName(bgName) {}

void BGObject::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";

	// assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(bgName, 0);
	texture->setRepeated(true);
	sprite->setTexture(*texture);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	// make BG height x k to emulate repeating BG.
	sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 10));
	GetTransformable()->setPosition(0, BaseRunner::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BG_Movement");
	AttachComponent(movement);

	Renderer* renderer = new Renderer("BG");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);

}
