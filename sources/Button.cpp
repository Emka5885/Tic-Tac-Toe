#include "Button.h"

Button::Button(sf::Vector2f size, sf::Text text, sf::Color hoverColor, sf::Color unhoverColor, sf::Color outlineColor, sf::Vector2f position, float zoomHover) : text(text), hoverColor(hoverColor), unhoverColor(unhoverColor), zoomHover(zoomHover)
{
	shape = sf::RectangleShape(size);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setPosition(position);
	shape.setFillColor(hoverColor);
	shape.setOutlineColor(outlineColor);

	// default outline thickness
	shape.setOutlineThickness(2);

	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(position);
}

Button::~Button()
{
}

void Button::ChangeHover(bool hover)
{
	if (hover && type == 0)
	{
		shape.setSize({ shape.getSize().x + zoomHover, shape.getSize().y + zoomHover });
		shape.setFillColor(hoverColor);
		type = 1;
	}
	else if(!hover && type == 1)
	{
		shape.setSize({ shape.getSize().x - zoomHover, shape.getSize().y - zoomHover });
		shape.setFillColor(unhoverColor);
		type = 0;
	}
}

void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}
