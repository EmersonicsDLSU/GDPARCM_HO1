#include "AnimObject.h"
#include <string>
#include "BaseRunner/BaseRunner.h"
#include "Components/Animation/Animator.h"
#include "Components/Renderer/Renderer.h"
#include "Utilities/Manager/TextureManager.h"

AnimObject::AnimObject(String name, std::vector<String> animations) : ::AGameObject(name), animations(animations) {}

void AnimObject::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";
	
	Animator* movement = new Animator(name, animations);
	AttachComponent(movement);

	// assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(animations[0], 0);
	sprite->setTexture(*texture);
	
	Renderer* renderer = new Renderer("Animation");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);

}
