#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"

class ScrollBar
{
private:
	sf::RectangleShape scrollBarBackground;
	sf::RectangleShape scrollBarHandle;

	sf::Vector2f position;
	int numberOfOptions;

	bool isDragging = false;
	sf::Vector2f dragOffset;

public:
	ScrollBar() {}
	ScrollBar(sf::Vector2f position, int numberOfOptions);

	void Init();
	void Update(ScrollBarHandleTypes type, sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetHandleShape();
};