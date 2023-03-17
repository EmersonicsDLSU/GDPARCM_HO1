#include "UIButton.h"
#include <iostream>
#include "UIButtonInputController.h"
#include "Components/Renderer/Renderer.h"
#include "UI/Buttons/ButtonListener.h"


UIButton::UIButton(string name, sf::Texture* normalTexture, sf::Texture* pressedTexture) : AGameObject(name)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

UIButton::~UIButton()
{
	AGameObject::~AGameObject();
}

void UIButton::Initialize()
{
	AGameObject::Initialize();

	sprite = new sf::Sprite();
	sprite->setTexture(*this->normalTexture);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);
}

void UIButton::SetButtonListener(ButtonListener* listener)
{
	std::cout << "Assign Button Listener " << "\n";
	//assign input controller
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController("UI_InputController", this->listener);
	AttachComponent(inputController);
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);

}

void UIButton::changeButtonToPressed()
{
	this->sprite->setTexture(*this->pressedTexture);
}

void UIButton::changeTexture(sf::Texture* normalTexture, sf::Texture* pressedTexture)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

sf::FloatRect UIButton::getLocalBounds() {
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::getGlobalBounds() {
	sf::FloatRect bounds = this->sprite->getGlobalBounds();
	bounds = getGlobalTransform().transformRect(bounds);
	return bounds;

}