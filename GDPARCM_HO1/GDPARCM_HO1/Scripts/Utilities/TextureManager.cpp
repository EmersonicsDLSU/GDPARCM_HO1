#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

#include <format>

#include "Typedefs.h"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::GetInstance() {
	//initialize only when we need it
	if (sharedInstance == nullptr) {
		sharedInstance = new TextureManager();
	}
	return sharedInstance;
}

void TextureManager::LoadAll() {

	LoadTexture("desert_bg", "../Media/Textures/Desert.png");
	sf::Texture* bgTex1;
	bgTex1 = GetTexture("desert_bg");
	bgTex1->setRepeated(true);
	// load the Dota2 icons
	for (int i = 0; i <= 479; ++i)
	{
		String iconName = std::format("tile{:03}", i);
		LoadTexture(iconName, 
			std::format("../Media/Streaming/{}.png", iconName));
	}

}

void TextureManager::LoadTexture(std::string key, std::string path) {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

sf::Texture* TextureManager::GetTexture(std::string key) {
	if (textureMap[key] != NULL) {
		return textureMap[key];
	}
	else {
		std::cout << "No texture found for " << key;
		return NULL;
	}
}