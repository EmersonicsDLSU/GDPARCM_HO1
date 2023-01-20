#include "BGMovement.h"
#include "BaseWindow/BaseWindow.h"
#include "Gameobjects/Utilities/AGameObject.h"

BGMovement::BGMovement(String name) : AComponent(name, Script)
{
}

BGMovement::~BGMovement()
{
}

void BGMovement::Perform()
{
	AComponent::Perform();

	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;

	sf::Transformable* bgTransform = GetOwner()->GetTransformable();
	bgTransform->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = GetOwner()->GetTransformable()->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		// reset position
		bgTransform->setPosition(0, -BaseWindow::WINDOW_HEIGHT * 7.0f);
	}
}

void BGMovement::SetBGSpeed(float speed)
{
	SPEED_MULTIPLIER = speed;
}

float BGMovement::GetBGSpeed()
{
	return SPEED_MULTIPLIER;
}
