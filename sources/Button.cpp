#include "Button.h"
#include "Definitions.h"

Button::Button(sf::Vector2f size, sf::Text text, sf::Color outlineColor, sf::Vector2f position, float zoom, sf::Color color) : unhoveredSize(size), text(text), unhoveredPosition(position), zoom(zoom)
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

	Init(outlineColor);
}

Button::~Button()
{
}

void Button::Init(sf::Color outlineColor)
{
	hoveredSize = { unhoveredSize.x + zoom, unhoveredSize.y + zoom };
	hoveredPosition = { unhoveredPosition.x - zoom / 2, unhoveredPosition.y - zoom / 2 };

	shape = sf::RectangleShape(unhoveredSize);
	shape.setOrigin(unhoveredSize.x / 2, unhoveredSize.y / 2);
	shape.setPosition(unhoveredPosition);
	shape.setFillColor(unhoverColor);
	shape.setOutlineColor(outlineColor);

	shape.setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);


	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 1.5);

	textShadow = text;
	textShadow.setFillColor(sf::Color::Black);
	textShadow.setPosition(unhoveredPosition.x + 4, unhoveredPosition.y + 3);

	text.setPosition(unhoveredPosition);
}

void Button::SetPosition(sf::Vector2f position)
{
	shape.setPosition(position);
	textShadow.setPosition(position.x + 4, position.y + 3);
	text.setPosition(position);
}

void Button::ChangeHover(bool hover)
{
	if (currentType == unhovered)
	{
		if (hover)
		{
			shape.setSize(hoveredSize);
			shape.setPosition(hoveredPosition);
			shape.setFillColor(hoverColor);
			currentType = hovered;
		}
	}
	else
	{
		if (!hover)
		{
			shape.setSize(unhoveredSize);
			shape.setPosition(unhoveredPosition);
			shape.setFillColor(unhoverColor);
			currentType = unhovered;
		}
	}
}

void Button::Clicked(bool isClicked)
{
	if (isClicked)
	{
		currentType = clicked;
		shape.setFillColor(clickColor);
	}
	else
	{
		ChangeHover(false);
	}
}

void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(textShadow);
	window.draw(text);
}

sf::RectangleShape& Button::GetShape()
{
	return shape;
}
