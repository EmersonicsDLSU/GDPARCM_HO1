#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities/Typedefs.h"

using namespace std;
class AGameObject; //perform forward declaration to avoid circular import dependency

class AComponent
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	AComponent(String name, ComponentType type);
	virtual ~AComponent();

	void AttachOwner(AGameObject* owner);
	void DetachOwner();
	AGameObject* GetOwner();
	ComponentType GetType();
	String GetName();

	void SetDeltaTime(sf::Time deltaTime);
	virtual void Perform(); //performs the associated action.
	virtual void Initialize();

protected:
	AGameObject* owner;
	ComponentType type;
	String name;
	sf::Time deltaTime;
};