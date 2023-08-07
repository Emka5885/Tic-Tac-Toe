#include "ScrollBar.h"
#include "Definitions.h"

ScrollBar::ScrollBar(sf::Vector2f position, int numberOfOptions) : position(position), numberOfOptions(numberOfOptions)
{
	Init();
}

void ScrollBar::Init()
{
	scrollBarBackground.setFillColor(sf::Color::Black);
	scrollBarBackground.setSize({ SCROLL_BAR_WIDTH, SCROLL_BAR_HEIGHT });
	scrollBarBackground.setOrigin(SCROLL_BAR_WIDTH / 2, SCROLL_BAR_HEIGHT / 2);
	scrollBarBackground.setPosition(position);
}
