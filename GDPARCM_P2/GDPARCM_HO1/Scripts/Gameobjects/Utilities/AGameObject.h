#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Components/Utilities/AComponent.h"

class AGameObject: sf::NonCopyable
{
public:
	typedef std::string String;
	AGameObject(String name);
	virtual ~AGameObject();
	virtual void Initialize();
	virtual void ProcessInput(sf::Event event);
	virtual void Update(sf::Time deltaTime);
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

	virtual void SetPosition(float x, float y);
	virtual void SetScale(float x, float y);
	virtual sf::FloatRect GetLocalBounds();
	virtual sf::FloatRect getGlobalBounds();
	sf::Transform getGlobalTransform();
	AGameObject* getParent();
	virtual sf::Vector2f GetPosition();
	virtual sf::Vector2f GetScale();

public:
	void AttachChild(AGameObject* child);
	void DetachChild(AGameObject* child);
	void AttachComponent(AComponent* component);
	void DetachComponent(AComponent* component);

	std::vector <AComponent*> GetComponentsOfType(AComponent::ComponentType type);
	/* TODO: Parent Child Transform
	std::vector <AComponent*> getComponentsOfTypeRecursive(AComponent::ComponentType type);
private:
	std::vector <AComponent*> getComponentsRecursiveProper(AGameObject* object,
		AComponent::ComponentType type, std::vector<AComponent*> foundList);
		*/
public:
	String GetName();
	sf::Sprite* GetSprite();
	void SetSprite(sf::Sprite* sprite);
	sf::Transformable* GetTransformable();
	void SetEnabled(bool flag);
	bool IsEnabled();

protected:
	String name;
	sf::Transformable _transformable;
	std::vector<AGameObject*> childList;
	std::vector<AComponent*> componentList;
	sf::Sprite* sprite;
	sf::Texture* texture;
	AGameObject* parent;

	float posX = 0.0f; float posY = 0.0f;
	float scaleX = 1.0f; float scaleY = 1.0f;
private:
	bool enabled = true;
};

