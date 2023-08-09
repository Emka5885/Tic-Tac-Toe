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
	float dragOffsetX;

public:
	ScrollBar() {}
	ScrollBar(sf::Vector2f position, int numberOfOptions);

	void Init();
	void Update(sf::Event event, sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetHandleShape();
};