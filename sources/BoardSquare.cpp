#include "BoardSquare.h"

BoardSquare::BoardSquare()
{
}

BoardSquare::BoardSquare(AssetManager& assets, sf::Vector2f position, sf::Color color) : assets(&assets), color(color)
{
	Init(position);
}

void BoardSquare::Init(sf::Vector2f position)
{
	shape.setSize({ 150, 150 });
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(8);
}

void BoardSquare::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void BoardSquare::ChangeBoardType(boardTypes type)
{
	if (type == empty)
	{
		boardType = empty;
		shape.setTexture(NULL);
		shape.setFillColor(color);
	}
	else if (type == x)
	{
		boardType = x;
		shape.setTexture(assets->GetTexture("x_image"));
		shape.setFillColor(sf::Color(xColor_r, xColor_g, xColor_b));
	}
	else
	{
		boardType = o;
		shape.setTexture(assets->GetTexture("o_image"));
		shape.setFillColor(sf::Color(oColor_r, oColor_g, oColor_b));
	}
}

sf::RectangleShape& BoardSquare::GetShape()
{
	return shape;
}

boardTypes BoardSquare::GetBoardType()
{
	return boardType;
}
