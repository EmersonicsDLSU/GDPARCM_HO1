#include "SpriteRenderer.h"

#include <SFML/Graphics/Sprite.hpp>
#include "Utilities/Manager/TextureManager.h"

SpriteRenderer::SpriteRenderer(string name, string textureName) : ::Renderer(name) {
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::GetInstance()->GetFromTextureMap(textureName, 0));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	//sprite->setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->AssignDrawable(sprite);
	this->mainSprite = sprite;
}
