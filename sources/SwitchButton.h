#pragma once
#include <SFML/Graphics.hpp>

enum SwitchButtonTypes { unhoveredSW, hoveredSW, clickedSW };

class SwitchButton
{
private:
	sf::RectangleShape shape;
	sf::Vector2f unhoverSize = { 100, 50 };
	sf::Vector2f hoverSize = { 100 + 4, 50 + 4 };
	sf::Vector2f position;
	sf::Vector2f hoverPosition = { position.x - 2, position.y - 2 };
	sf::Text text;
	bool active;

	sf::Color unhoverActiveColor = sf::Color(165, 165, 165);
	sf::Color hoverActiveColor = sf::Color(145, 145, 145);
	sf::Color unhoverInactiveColor = sf::Color(105, 105, 105);
	sf::Color hoverInactiveColor = sf::Color(85, 85, 85);

	SwitchButtonTypes currentType = unhoveredSW;

public:
	SwitchButton();
	SwitchButton(sf::Vector2f position, sf::Text text, bool active = false);

	void Init();
	void ChangeHover(bool hover);
	void ChangeInActivity(bool isActive = true);
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape& GetShape();
	bool& GetActive();
};