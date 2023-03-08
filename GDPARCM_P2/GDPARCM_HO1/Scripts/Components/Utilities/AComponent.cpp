#include "AComponent.h"

#include "Gameobjects/Utilities/AGameObject.h"

AComponent::AComponent(String name, ComponentType type) {
	this->name = name;
	this->owner = nullptr;
	this->type = type;
}

AComponent::~AComponent() {
	this->owner = nullptr;
	this->type = NotSet;
}

// parent
AGameObject* AComponent::GetOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::GetType() {
	return this->type;
}

String AComponent::GetName()
{
	return this->name;
}

void AComponent::SetDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}

void AComponent::Perform()
{
	//std::cout << "Component's Name: " << GetName() << std::endl;
}

void AComponent::Initialize()
{
}

void AComponent::AttachOwner(AGameObject* object) {
	this->owner = object;
	std::cout << "Attached owner: " << object->GetName() << std::endl;
}

void AComponent::DetachOwner() {
	// if object owner gets detached. then component must also be deleted.
	delete this;
}