#include "SwitchButton.h"

SwitchButton::SwitchButton()
{
}

SwitchButton::SwitchButton(sf::Vector2f position, sf::Text text, bool active) : position(position), text(text), active(active)
{
	Init();
}

void SwitchButton::Init()
{
	if (active)
	{
		shape.setFillColor(unhoverActiveColor);
	}
	else
	{
		shape.setFillColor(unhoverInactiveColor);
	}
	shape.setSize(unhoverSize);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setPosition(position);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2);

	text.setPosition(position);
}

void SwitchButton::ChangeHover(bool hover)
{
	if (currentType == unhoveredSW)
	{
		if (hover)
		{
			currentType = hoveredSW;
			shape.setSize(hoverSize);
			shape.setPosition(hoverPosition);
			shape.setFillColor(hoverInactiveColor);
		}
	}
	else
	{
		if (!hover)
		{
			currentType = unhoveredSW;
			shape.setSize(unhoverSize);
			shape.setPosition(position);
			shape.setFillColor(unhoverInactiveColor);
		}
	}
}

void SwitchButton::ChangeInActivity(bool isActive)
{
	if (isActive)
	{
		if (!active)
		{
			active = true;
			shape.setFillColor(unhoverActiveColor);
			shape.setSize(unhoverSize);
			shape.setPosition(position);
			currentType = hoveredSW;
		}
	}
	else
	{
		if (active)
		{
			active = false;
			currentType = unhoveredSW;
			shape.setFillColor(unhoverInactiveColor);
		}
	}
}

void SwitchButton::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

sf::RectangleShape& SwitchButton::GetShape()
{
	return shape;
}

bool& SwitchButton::GetActive()
{
	return active;
}
