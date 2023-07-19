#include "Button.h"

Button::Button(sf::Vector2f size, sf::Text text, sf::Color outlineColor, sf::Vector2f position, float zoom, sf::Color color) : text(text), zoom(zoom)
{
	unhoverColor.r = std::clamp(int(color.r), 45, 255);
	unhoverColor.g = std::clamp(int(color.g), 45, 255);
	unhoverColor.b = std::clamp(int(color.b), 45, 255);

	hoverColor.r = unhoverColor.r - 25;
	hoverColor.g = unhoverColor.g - 25;
	hoverColor.b = unhoverColor.b - 25;

	clickColor.r = unhoverColor.r - 45;
	clickColor.g = unhoverColor.g - 45;
	clickColor.b = unhoverColor.b - 45;

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
	shape.setFillColor(unhoverColor);
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
	switch (currentType)
	{
	case unhovered:
		if (hover)
		{
			shape.setSize({ shape.getSize().x + zoom, shape.getSize().y + zoom });
			shape.setPosition(shape.getPosition().x - zoom / 2, shape.getPosition().y - zoom / 2);
			shape.setFillColor(hoverColor);
			currentType = hovered;
		}
		break;

	case hovered:
		if (!hover)
		{
			shape.setSize({ shape.getSize().x - zoom, shape.getSize().y - zoom });
			shape.setPosition(shape.getPosition().x + zoom / 2, shape.getPosition().y + zoom / 2);
			shape.setFillColor(unhoverColor);
			currentType = unhovered;
		}
		break;

	case clicked:
		break;
	}
}

void Button::Clicked()
{
	currentType = clicked;
	shape.setFillColor(clickColor);
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

void Button::SetPosition(sf::Vector2f position)
{
	shape.setPosition(position);
	textShadow.setPosition(position.x + 4, position.y + 3);
	text.setPosition(position);
}
