#pragma once
#include "Components/Utilities/AComponent.h"

//class for simply storing the event data. may be expanded to handle basic controls.
class GenericInputController : public AComponent
{
public:
	GenericInputController(string name);
	~GenericInputController();

	void Perform() override;
	void assignEvent(sf::Event event);

protected:
	sf::Event event;
};
