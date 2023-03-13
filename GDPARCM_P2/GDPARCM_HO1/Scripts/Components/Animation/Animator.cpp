#include "Animator.h"
#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/Utilities/AGameObject.h"
#include "Utilities/Manager/TextureManager.h"

Animator::Animator(String name, std::vector<String> animations) : AComponent(name, Script)
{
	// assign texture
	for (int i = 0; i < animations.size(); ++i)
	{
		sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(animations[i], 0);
		this->animations.push_back(texture);
	}
}

Animator::~Animator()
{
}

void Animator::Perform()
{
	ticks += deltaTime.asSeconds();

	if (ticks >= _animInterval)
	{
		if (++currentAnim >= animations.size()) currentAnim = 0;
		GetOwner()->GetSprite()->setTexture(*(this->animations[currentAnim]));
		ticks = 0;
	}

	AComponent::Perform();
}

void Animator::Initialize()
{
	AComponent::Initialize();
	
}

void Animator::SetInterval(float interval)
{
	_animInterval = interval;
}
