#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Definitions.h"

class BoardSquare
{
private:
	sf::RectangleShape shape;
	sf::Color color;
	
	boardTypes boardType = empty;

	AssetManager* assets;

public:
	BoardSquare();
	BoardSquare(AssetManager& assets, sf::Vector2f position, sf::Color color = { 120, 120, 120 });
	~BoardSquare() { }

	void Init(sf::Vector2f position);
	void Draw(sf::RenderWindow& window);

	void ChangeBoardType(boardTypes type);

	sf::RectangleShape& GetShape();

	boardTypes GetBoardType();
};