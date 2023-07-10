#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f size, sf::Text text, sf::Color color, sf::Color outlineColor, sf::Vector2f position, float zoom) : text(text), zoom(zoom)
{
	if (color.r > 255)
	{
		color.r = 255;
	}
	else if (color.r < 45)
	{
		color.r = 45;
	}

	if (color.g > 255)
	{
		color.g = 255;
	}
	else if (color.g < 45)
	{
		color.g = 45;
	}

	if (color.b > 255)
	{
		color.b = 255;
	}
	else if (color.b < 45)
	{
		color.b = 45;
	}

	this->color = color;

	Init(size, position, outlineColor);
}

Button::~Button()
{
}

void Button::Init(sf::Vector2f size, sf::Vector2f position, sf::Color outlineColor)
{
	shape = sf::RectangleShape(size);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setOutlineColor(outlineColor);

	// default outline thickness
	shape.setOutlineThickness(4);


	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 1.5);

	textShadow = text;
	textShadow.setFillColor(sf::Color::Black);
	textShadow.setPosition(position.x + 4, position.y + 3);

	text.setPosition(position);
}

void Button::ChangeHover(bool hover)
{
	if (hover && type == 0)
	{
		shape.setSize({ shape.getSize().x + zoom, shape.getSize().y + zoom });
		shape.setPosition(shape.getPosition().x - zoom / 2, shape.getPosition().y - zoom / 2);
		shape.setFillColor(sf::Color(color.r - 25, color.g - 25, color.b - 25));
		type = 1;
	}
	else if (!hover && type == 1)
	{
		shape.setSize({ shape.getSize().x - zoom, shape.getSize().y - zoom });
		shape.setPosition(shape.getPosition().x + zoom / 2, shape.getPosition().y + zoom / 2);
		shape.setFillColor(color);
		type = 0;
	}
}

void Button::Clicked()
{
	type = 2;
	shape.setFillColor(sf::Color(color.r - 45, color.g - 45, color.b - 45));
}

void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(textShadow);
	window.draw(text);
}

sf::RectangleShape Button::GetShape()
{
	return shape;
}
