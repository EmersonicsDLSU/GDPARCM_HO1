#include "IconObject.h"

#include "Components/Renderer/Renderer.h"
#include "Components/Renderer/TextureDisplay.h"
#include "Utilities/Manager/TextureManager.h"

IconObject::IconObject(String name, int textureIndex): AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::Initialize()
{
	AGameObject::Initialize();
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetStreamTextureFromList(this->textureIndex);
	this->sprite->setTexture(*texture);

	

	Renderer* renderer = new Renderer(name + std::to_string(textureIndex));
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}

