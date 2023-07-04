#pragma once
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 800

class AssetManager
{
public:
	AssetManager();
	~AssetManager() { }

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture* GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
};