#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

enum ButtonTypes { unhovered, hovered, clicked };

class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Text textShadow;
	sf::Color unhoverColor;
	sf::Color hoverColor;
	sf::Color clickColor;
	ButtonTypes currentType = unhovered;
	float zoom;
	sf::Vector2f unhoveredSize;
	sf::Vector2f hoveredSize;
	sf::Vector2f unhoveredPosition;
	sf::Vector2f hoveredPosition;

public:
	Button() {}
	Button(sf::Vector2f size, sf::Text text, sf::Color outlineColor, sf::Vector2f position, float zoom, sf::Color color = sf::Color({ 115, 115, 115 }));
	~Button();

	void Init(sf::Color outlineColor);

	void SetPosition(sf::Vector2f position);
	void ChangeHover(bool hover);
	void Clicked(bool isClicked = true);
	void DrawButton(sf::RenderWindow& window);

	sf::RectangleShape& GetShape();
};