#pragma once
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	AssetManager();
	~AssetManager() { }

	void InitFonts();

	void LoadTexture(const char* name, const char* fileName);
	sf::Texture* GetTexture(const char* name);

	void LoadFont(const char* name, const char* fileName);
	sf::Font& GetFont(const char* name);

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
};