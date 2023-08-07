#pragma once
#include <SFML/Graphics.hpp>

class ScrollBar
{
private:
	sf::RectangleShape scrollBarBackground;
	sf::RectangleShape scrollBarHandle;

	sf::Vector2f position;
	int numberOfOptions;

public:
	ScrollBar(sf::Vector2f position, int numberOfOptions);

	void Init();
};