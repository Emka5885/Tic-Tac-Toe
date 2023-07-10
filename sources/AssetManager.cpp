#include "AssetManager.h"
#include "Definitions.h"

AssetManager::AssetManager()
{
	InitFonts();
	InitTextures();
}

void AssetManager::InitFonts()
{
	LoadFont(defaultFont, defaultFont_path);
}

void AssetManager::InitTextures()
{
	LoadTexture(icon, icon_path);
}

void AssetManager::LoadTexture(const char* name, const char* fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(fileName))
	{
		this->textures[name] = texture;
	}
}

sf::Texture* AssetManager::GetTexture(const char* name)
{
	return &this->textures.at(name);
}

void AssetManager::LoadFont(const char* name, const char* fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		this->fonts[name] = font;
	}
}

sf::Font& AssetManager::GetFont(const char* name)
{
	return this->fonts.at(name);
}