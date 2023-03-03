#include "TextRenderer.h"
#include "Utilities/Manager/FontManager.h"

TextRenderer::TextRenderer(sf::Text* text, std::string name, const sf::Color& fillColor,
	const sf::Color& outlineColor, float outlineThickness, float size, std::string defaultText) : Renderer(name)
{
	sf::Font* font = FontManager::GetInstance()->GetFont("default");
	text->setFont(*font);
	text->setFillColor(fillColor);
	text->setOutlineColor(outlineColor);
	text->setOutlineThickness(outlineThickness);
	text->setCharacterSize(size);
	text->setString(defaultText);
	this->AssignDrawable(text);
}

TextRenderer* TextRenderer::CreateText(sf::Text* textDrawable, std::string name, const sf::Color& fillColor, const sf::Color& outlineColor,
	float outlineThickness, float size, std::string defaultText)
{
	return new TextRenderer(textDrawable, name, fillColor, outlineColor, outlineThickness, size, defaultText);
}