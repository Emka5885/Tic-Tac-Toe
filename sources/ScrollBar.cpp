#include "ScrollBar.h"

ScrollBar::ScrollBar(sf::Vector2f position, int numberOfOptions) : position(position), numberOfOptions(numberOfOptions)
{
	Init();
}

void ScrollBar::Init()
{
	scrollBarBackground.setFillColor(sf::Color::White);
	scrollBarBackground.setOutlineColor(sf::Color::Black);
	scrollBarBackground.setOutlineThickness(2);
	scrollBarBackground.setSize({ SCROLL_BAR_WIDTH, SCROLL_BAR_HEIGHT });
	scrollBarBackground.setOrigin(SCROLL_BAR_WIDTH / 2, SCROLL_BAR_HEIGHT / 2);
	scrollBarBackground.setPosition(position);

	scrollBarHandle.setFillColor(sf::Color(155, 155, 155));
	scrollBarHandle.setOutlineColor(sf::Color::Black);
	scrollBarHandle.setOutlineThickness(2);
	scrollBarHandle.setSize({ SCROLL_BAR_WIDTH / numberOfOptions, SCROLL_BAR_HEIGHT * 3.5 });
	scrollBarHandle.setOrigin(scrollBarHandle.getSize().x / 2, scrollBarHandle.getSize().y / 2);
	scrollBarHandle.setPosition(position.x - SCROLL_BAR_WIDTH / 2, position.y);
}

void ScrollBar::Update(ScrollBarHandleTypes type, sf::Vector2f mousePos)
{
	if (type == pressed)
	{
		isDragging = true;
		dragOffset = mousePos - scrollBarHandle.getPosition();
	}
	else if (type == released)
	{
		isDragging = false;
	}
	else if (type == moved && isDragging)
	{
		float maxHandleOffset = SCROLL_BAR_WIDTH - scrollBarHandle.getSize().x;
		float newHandleOffset = mousePos.x - scrollBarBackground.getPosition().x / 2 - dragOffset.x;
		newHandleOffset = std::max(0.0f, std::min(newHandleOffset, maxHandleOffset));
		scrollBarHandle.setPosition(scrollBarBackground.getPosition().x / 2 + newHandleOffset, scrollBarHandle.getPosition().y);
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
