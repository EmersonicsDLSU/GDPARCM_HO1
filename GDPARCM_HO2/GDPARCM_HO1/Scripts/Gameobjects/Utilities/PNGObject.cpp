#include "PNGObject.h"

#include "Components/Renderer/Renderer.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Utilities/Manager/TextureManager.h"

PNGObject::PNGObject(String name) : AGameObject(name)
{

}

void PNGObject::Initialize()
{
	AGameObject::Initialize();
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(name, 0);
	this->sprite->setTexture(*texture);

	Renderer* renderer = new Renderer(name);
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}

