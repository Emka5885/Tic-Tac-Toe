#pragma once
#include "AssetManager.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	sf::Vector2i GetMousePosition(sf::RenderWindow& window);

	bool isButtonHovered(sf::RectangleShape object, sf::RenderWindow& window);
	bool isButtonClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window);
};