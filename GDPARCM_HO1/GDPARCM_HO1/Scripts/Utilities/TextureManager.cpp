#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

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

	//LoadTexture("ui_bg", "Media/Textures/newtxtbx.png");
	//LoadTexture("btn_normal", "Media/Textures/newbt.png");
	//LoadTexture("btn_pressed", "Media/Textures/newbtpress.png");
	//LoadTexture("hud_bg", "Media/Textures/clear.png");
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