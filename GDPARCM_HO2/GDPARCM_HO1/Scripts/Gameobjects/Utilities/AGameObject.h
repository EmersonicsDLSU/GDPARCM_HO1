#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Components/Utilities/AComponent.h"

class AGameObject: sf::NonCopyable
{
	public:
		typedef std::string String;
	AGameObject(String name);
		~AGameObject();
		virtual void Initialize();
		virtual void ProcessInput(sf::Event event);
		virtual void Update(sf::Time deltaTime);
		virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

		virtual void SetPosition(float x, float y);
		virtual void SetScale(float x, float y);
		virtual sf::FloatRect GetLocalBounds();
		virtual sf::Vector2f GetPosition();
		virtual sf::Vector2f GetScale();

public:
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
	sf::Transformable* GetTransformable();
	void SetEnabled(bool flag);
	bool IsEnabled();

	protected:
		String name;
		sf::Transformable _transformable;
		std::vector<AComponent*> componentList;
		sf::Sprite* sprite;
		sf::Texture* texture;

		float posX = 0.0f; float posY = 0.0f;
		float scaleX = 1.0f; float scaleY = 1.0f;
private:
	bool enabled = true;
};

