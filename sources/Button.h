#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Text textShadow;
	sf::Color color;
	int type = 0;   // 0 = unhovered, 1 = hovered, 2 = clicked
	float zoom;

public:
	Button() {}
	Button(sf::Vector2f size, sf::Text text, sf::Color color, sf::Color outlineColor, sf::Vector2f position, float zoom);
	~Button();

	void Init(sf::Vector2f size, sf::Vector2f position, sf::Color outlineColor);

	void ChangeHover(bool hover);
	void Clicked();
	void DrawButton(sf::RenderWindow& window);

	sf::RectangleShape GetShape();
};