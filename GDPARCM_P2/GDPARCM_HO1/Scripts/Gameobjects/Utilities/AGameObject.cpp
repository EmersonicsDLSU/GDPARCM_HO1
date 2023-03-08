#include "AGameObject.h"
#include "Components/Renderer/Renderer.h"


AGameObject::AGameObject(String name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	if (sprite != nullptr)
		delete sprite;
	if (texture != nullptr)
		delete texture;
	std::cout << "Object Name: " << GetName() << " deleted\n";
}

void AGameObject::Initialize()
{
}

void AGameObject::ProcessInput(sf::Event event)
{
}

void AGameObject::Update(sf::Time deltaTime)
{
	// updates all the components attached to this gameobject
	std::vector<AComponent*> componentList = this->GetComponentsOfType(AComponent::ComponentType::Script);
	for (int j = 0; j < componentList.size(); j++) {
		componentList[j]->SetDeltaTime(deltaTime);
		componentList[j]->Perform();
	}
}

void AGameObject::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	// check if this gameobject is enabled
	if (!IsEnabled()) {
		return;
	}

	std::vector<AComponent*> componentList = this->GetComponentsOfType(AComponent::ComponentType::Renderer);

	renderStates.transform = renderStates.transform * _transformable.getTransform();

	// draws the spriteRenderer of this gameobject
	for (int j = 0; j < componentList.size(); j++) {
		Renderer* renderer = (Renderer*)componentList[j];
		renderer->AssignTargetWindow(targetWindow);
		renderer->SetRenderStates(renderStates);
		renderer->Perform();
	}
}

void AGameObject::SetPosition(float x, float y)
{
	_transformable.setPosition(x, y);
}

void AGameObject::SetScale(float x, float y)
{
	_transformable.setScale(x, y);
}

sf::FloatRect AGameObject::GetLocalBounds()
{
	return this->sprite->getLocalBounds();
}

sf::FloatRect AGameObject::getGlobalBounds()
{
	throw "gtLocalBounds() not implemented!";
}

sf::Transform AGameObject::getGlobalTransform()
{
	AGameObject* parentObj = this;
	vector<AGameObject*> parentList;
	while (parentObj != NULL) {
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--) {
		transform = transform * parentList[i]->GetTransformable()->getTransform();
	}
	return transform;
}

AGameObject* AGameObject::getParent()
{
	return this->parent;
}

sf::Vector2f AGameObject::GetPosition()
{
	return _transformable.getPosition();
}

sf::Vector2f AGameObject::GetScale()
{
	return _transformable.getScale();
}

void AGameObject::AttachChild(AGameObject* child)
{
	this->childList.push_back(child);
	child->parent = this;
	child->Initialize(); //initialize when attaching to child
}

void AGameObject::DetachChild(AGameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) {
		if (this->childList[i] == child) {
			index = i;
		}
	}

	if (index != -1) {
		this->childList.erase(this->childList.begin() + index);
	}
}

void AGameObject::AttachComponent(AComponent* component)
{
	componentList.push_back(component);
	component->AttachOwner(this);
	component->Initialize();
}

void AGameObject::DetachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i] == component) {
			index = i;
			componentList[i]->DetachOwner();
			break;
		}
	}
	if (index != -1) {
		componentList.erase(componentList.begin() + index);
	}
}

// gets all the components<can be a specific type> of this gameobject
std::vector<AComponent*> AGameObject::GetComponentsOfType(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

/*
std::vector<AComponent*> AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < this->childList.size(); i++) {
		foundList = this->getComponentsRecursiveProper(this->childList[i], type, foundList);
	}

	return foundList;
}
*/

/*
std::vector<AComponent*> AGameObject::getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type,
	std::vector<AComponent*> foundList)
{
	std::vector<AGameObject*> children = object->childList;

	for (int i = 0; i < object->componentList.size(); i++) {
		if (object->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < children.size(); i++) {
		this->getComponentsRecursiveProper(children[i], type, foundList);
	}

	return foundList;
}
*/

String AGameObject::GetName()
{
	return name;
}

sf::Sprite* AGameObject::GetSprite()
{
	return sprite;
}

void AGameObject::SetSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

sf::Transformable* AGameObject::GetTransformable()
{
	return &_transformable;
}

void AGameObject::SetEnabled(bool flag)
{
	enabled = flag;
}

bool AGameObject::IsEnabled()
{
	return enabled;
}
