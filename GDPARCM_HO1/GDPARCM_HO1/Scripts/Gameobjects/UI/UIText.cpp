#include "UIText.h"

#include "Components/Renderer/Renderer.h"
#include "Utilities/FontManager.h"

UIText::UIText(String name) : AGameObject(name)
{
	text = new sf::Text();
}

UIText::~UIText()
{
}

void UIText::Initialize()
{
	AGameObject::Initialize();

	//declare a text to be used
	//font must be a pointer or else it gets immediately de-allocated.
	sf::Font* font = FontManager::GetInstance()->GetFont("default");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4.0f);
	SetSize(40);
	SetText("<Using placeholder!>");

	Renderer* renderer = new Renderer("Text");
	renderer->AssignDrawable(text);
	this->AttachComponent(renderer);
}

void UIText::SetText(String text)
{
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();
	// Align center, you can put other alignment here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

String UIText::GetText()
{
	return text->getString();
}

void UIText::SetSize(unsigned size)
{
	this->text->setCharacterSize(size);
}
