
#pragma once
#include "Components/Utilities/AComponent.h"

enum class RendererType { Custom, Sprite };
class Renderer : public AComponent
{
public:

	Renderer(string name);
	virtual ~Renderer();
	void AssignTargetWindow(sf::RenderWindow* window);
	void AssignDrawable(sf::Drawable* drawable);
	void SetRenderStates(sf::RenderStates renderStates);

	void Perform() override;

	static Renderer* Create(string name, string resourcesName, RendererType rendererType);
	static Renderer* CreateSprite(string name, string resourceName);

	sf::Sprite* mainSprite;
protected:
	//used to be private, now we moved to protected since we're extending
	sf::Drawable* drawable = NULL;
private:
	sf::RenderWindow* targetWindow = NULL;

	sf::RenderStates renderStates = sf::RenderStates::Default;

};
