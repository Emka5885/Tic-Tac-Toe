#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"

class Slider
{
private:
	sf::RectangleShape sliderBackground;
	sf::RectangleShape sliderHandle;

	sf::Vector2f position;
	int numberOfOptions = 0;
	int currentNumber = 0;

	bool isDragging = false;
	float dragOffsetX = 0;

public:
	Slider();
	Slider(sf::Vector2f position, int numberOfOptions, int currentNumber);

	void Init();
	void Update(sf::Event event, sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetHandleShape();

	int& GetCurrentNumber();
};