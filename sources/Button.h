#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Color hoverColor;
	sf::Color unhoverColor;
	int type = 0;   // 0 = unhover, 1 = hover
	float zoomHover;

public:
	Button(sf::Vector2f size, sf::Text text, sf::Color hoverColor, sf::Color unhoverColor, sf::Color outlineColor, sf::Vector2f position, float zoomHover);
	~Button();

	void ChangeHover(bool hover);
	void DrawButton(sf::RenderWindow& window);
};