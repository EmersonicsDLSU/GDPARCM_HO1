#include "FontManager.h"
#include <iostream>

FontManager* FontManager::sharedInstance = nullptr;

FontManager* FontManager::GetInstance() {
	//initialize only when we need it
	if (sharedInstance == nullptr) {
		sharedInstance = new FontManager();
	}
	return sharedInstance;
}

void FontManager::LoadAll() {

	LoadFont("default", "../GDPARCM_HO1/Media/Sansation.ttf");

}

void FontManager::LoadFont(std::string key, std::string path) {
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}

sf::Font* FontManager::GetFont(std::string key) {
	if (fontMap[key] != nullptr) {
		return fontMap[key];
	}
	else {
		std::cout << "No font found for " << key;
		return NULL;
	}
}