#include "Slider.h"
#include <iostream>

Slider::Slider()
{
}

Slider::Slider(sf::Vector2f position, int numberOfOptions, int currentNumber) : position(position), numberOfOptions(numberOfOptions), currentNumber(currentNumber)
{
	Init();
}

void Slider::Init()
{
	std::clamp(currentNumber, 0, 100);

	sliderBackground.setFillColor(sf::Color(185,185,185));
	sliderBackground.setOutlineColor(sf::Color::Black);
	sliderBackground.setOutlineThickness(2);
	sliderBackground.setSize({ SCROLL_BAR_WIDTH, SCROLL_BAR_HEIGHT });
	sliderBackground.setOrigin(SCROLL_BAR_WIDTH / 2, SCROLL_BAR_HEIGHT / 2);
	sliderBackground.setPosition(position);

	sliderHandle.setFillColor(sf::Color::White);
	sliderHandle.setOutlineColor(sf::Color::Black);
	sliderHandle.setOutlineThickness(2);
	sliderHandle.setSize({ SCROLL_BAR_WIDTH / numberOfOptions, SCROLL_BAR_HEIGHT * 3.5 });
	sliderHandle.setOrigin(sliderHandle.getSize().x / 2, sliderHandle.getSize().y / 2);
	sliderHandle.setPosition(position.x - SCROLL_BAR_WIDTH / 2 + currentNumber / (100 / float(numberOfOptions)) * SCROLL_BAR_WIDTH / numberOfOptions, position.y);
}

void Slider::Update(sf::Event event, sf::Vector2f mousePos)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (sliderHandle.getGlobalBounds().contains(mousePos))
		{
			isDragging = true;
			dragOffsetX = mousePos.x - sliderHandle.getPosition().x;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		isDragging = false;
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (isDragging)
		{
			float maxHandleOffset = SCROLL_BAR_WIDTH / 2 + sliderBackground.getPosition().x - sliderHandle.getSize().x / 2;
			float newHandleOffset = mousePos.x - dragOffsetX;
			newHandleOffset = std::max(WIDTH / 2 - SCROLL_BAR_WIDTH / 2, std::min(newHandleOffset, maxHandleOffset));
			sliderHandle.setPosition(newHandleOffset, sliderHandle.getPosition().y);

			currentNumber = (newHandleOffset - (WIDTH / 2 - SCROLL_BAR_WIDTH / 2)) * 100 / SCROLL_BAR_WIDTH;
		}
	}
}

void Slider::Draw(sf::RenderWindow& window)
{
	window.draw(sliderBackground);
	window.draw(sliderHandle);
}

sf::RectangleShape Slider::GetHandleShape()
{
	return sliderHandle;
}

int& Slider::GetCurrentNumber()
{
	return currentNumber;
}
