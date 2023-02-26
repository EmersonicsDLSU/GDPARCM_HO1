#pragma once
#include <SFML/Graphics.hpp>;
#include <unordered_map>

class FontManager
{
public:
    static FontManager* GetInstance();

    void LoadAll();
    sf::Font* GetFont(std::string);
private:
    // set constructor to private
    FontManager() {};
    // set copy contructor to private
    FontManager(FontManager const&) {};
    // assignment operator is private
    FontManager& operator=(FontManager const&) {};
    static FontManager* sharedInstance;

    void LoadFont(std::string, std::string);
    std::unordered_map<std::string, sf::Font*> fontMap;
};