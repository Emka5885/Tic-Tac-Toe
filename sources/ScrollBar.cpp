#include "ScrollBar.h"
#include <iostream>

ScrollBar::ScrollBar(sf::Vector2f position, int numberOfOptions, int currentNumber) : position(position), numberOfOptions(numberOfOptions), currentNumber(currentNumber)
{
	Init();
}

void ScrollBar::Init()
{
	std::clamp(currentNumber, 0, 100);

	scrollBarBackground.setFillColor(sf::Color(185,185,185));
	scrollBarBackground.setOutlineColor(sf::Color::Black);
	scrollBarBackground.setOutlineThickness(2);
	scrollBarBackground.setSize({ SCROLL_BAR_WIDTH, SCROLL_BAR_HEIGHT });
	scrollBarBackground.setOrigin(SCROLL_BAR_WIDTH / 2, SCROLL_BAR_HEIGHT / 2);
	scrollBarBackground.setPosition(position);

	scrollBarHandle.setFillColor(sf::Color::White);
	scrollBarHandle.setOutlineColor(sf::Color::Black);
	scrollBarHandle.setOutlineThickness(2);
	scrollBarHandle.setSize({ SCROLL_BAR_WIDTH / numberOfOptions, SCROLL_BAR_HEIGHT * 3.5 });
	scrollBarHandle.setOrigin(scrollBarHandle.getSize().x / 2, scrollBarHandle.getSize().y / 2);
	scrollBarHandle.setPosition(position.x - SCROLL_BAR_WIDTH / 2 + currentNumber / (100 / float(numberOfOptions)) * SCROLL_BAR_WIDTH / numberOfOptions, position.y);
}

void ScrollBar::Update(sf::Event event, sf::Vector2f mousePos)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (scrollBarHandle.getGlobalBounds().contains(mousePos))
		{
			isDragging = true;
			dragOffsetX = mousePos.x - scrollBarHandle.getPosition().x;
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
			float maxHandleOffset = SCROLL_BAR_WIDTH / 2 + scrollBarBackground.getPosition().x - scrollBarHandle.getSize().x / 2;
			float newHandleOffset = mousePos.x - dragOffsetX;
			newHandleOffset = std::max(WIDTH / 2 - SCROLL_BAR_WIDTH / 2, std::min(newHandleOffset, maxHandleOffset));
			scrollBarHandle.setPosition(newHandleOffset, scrollBarHandle.getPosition().y);

			currentNumber = (newHandleOffset - (WIDTH / 2 - SCROLL_BAR_WIDTH / 2)) * 100 / SCROLL_BAR_WIDTH;
		}
	}
}

void ScrollBar::Draw(sf::RenderWindow& window)
{
	window.draw(scrollBarBackground);
	window.draw(scrollBarHandle);
}

sf::RectangleShape ScrollBar::GetHandleShape()
{
	return scrollBarHandle;
}

int& ScrollBar::GetCurrentNumber()
{
	return currentNumber;
}
