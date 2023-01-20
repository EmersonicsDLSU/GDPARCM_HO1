#pragma once
#include <SFML/Graphics.hpp>;
#include <unordered_map>
#include <string>
#include <vector>

class TextureManager
{
public:
    static TextureManager* GetInstance();

    void LoadAll();
    sf::Texture* GetTexture(std::string);
private:
    // set constructor to private
    TextureManager() {};
    // set copy contructor to private
    TextureManager(TextureManager const&) {};
    // assignment operator is private
    TextureManager& operator=(TextureManager const&) {};
    static TextureManager* sharedInstance;

    void LoadTexture(std::string, std::string);
    std::unordered_map<std::string, sf::Texture*> textureMap;

public:
    std::vector<std::string> listOfProperties;
    sf::Texture jsonTexture;
};