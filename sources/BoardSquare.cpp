#include "BoardSquare.h"

BoardSquare::BoardSquare(sf::Vector2f position, sf::Color color)
{
	Init(position, color);
}

void BoardSquare::Init(sf::Vector2f position, sf::Color color)
{
	shape.setSize({ 150, 150 });
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(8);
}

void BoardSquare::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
