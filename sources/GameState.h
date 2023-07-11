#pragma once
#include "State.h"
#include "Game.h"
#include "BoardSquare.h"

class GameState :public State
{
public:
	GameState(GameDataReference data, sf::Text title, sf::Text titleShadow);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference data;

	sf::Text title;
	sf::Text titleShadow;

	std::vector<BoardSquare> boardSquares;
};