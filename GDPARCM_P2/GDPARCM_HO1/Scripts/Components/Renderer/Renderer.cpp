#include "Renderer.h"

#include "SpriteRenderer.h"

Renderer::Renderer(string name) : AComponent(name, AComponent::Renderer)
{
	this->type = AComponent::Renderer;
	this->renderStates = sf::RenderStates::Default;
}

Renderer::~Renderer()
{
	delete this->drawable;
}

void Renderer::AssignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}

void Renderer::AssignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}

void Renderer::SetRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}

void Renderer::Perform() {
	AComponent::Perform();

	this->targetWindow->draw(*this->drawable, this->renderStates);
}

Renderer* Renderer::Create(string name, string resourceName, RendererType rendererType) {
	switch (rendererType) {
	case RendererType::Sprite:
		return new SpriteRenderer(name, resourceName);
		break;
	case RendererType::Custom:
	default:
		return new Renderer(name);
	}
}

Renderer* Renderer::CreateSprite(string name, string resourceName) {
	return Renderer::Create(name, resourceName, RendererType::Sprite);
}
