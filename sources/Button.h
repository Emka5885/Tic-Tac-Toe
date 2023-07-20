#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

enum types { unhovered, hovered, clicked };

class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Text textShadow;
	sf::Color unhoverColor;
	sf::Color hoverColor;
	sf::Color clickColor;
	types currentType = unhovered;
	float zoom;

public:
	Button() {}
	Button(sf::Vector2f size, sf::Text text, sf::Color outlineColor, sf::Vector2f position, float zoom, sf::Color color = sf::Color({ 115, 115, 115 }));
	~Button();

	void Init(sf::Vector2f size, sf::Vector2f position, sf::Color outlineColor);

	void ChangeHover(bool hover);
	void Clicked();
	void DrawButton(sf::RenderWindow& window);

	void SetPosition(sf::Vector2f position);
	sf::RectangleShape& GetShape();
};