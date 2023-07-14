#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"

class BoardSquare
{
private:
	sf::RectangleShape shape;

public:
	BoardSquare() { }
	BoardSquare(sf::Vector2f position, sf::Color color = { 120, 120, 120 });
	~BoardSquare() { }

	void Init(sf::Vector2f position, sf::Color color);
	void Draw(sf::RenderWindow& window);
};