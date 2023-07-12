#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Widgets
{
private:
	sf::Text totalsText;
	sf::Text scoreText;
	sf::Text playersText;

	std::string p1;
	std::string p2;

	AssetManager assets;

public:
	Widgets(AssetManager& assets, std::string p1 = "Player 1", std::string p2 = "Player 2");
	~Widgets();

	void Init();
	void Draw(sf::RenderWindow& window);
};