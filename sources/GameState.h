#pragma once
#include "State.h"
#include "Game.h"
#include "BoardSquare.h"
#include "Widgets.h"

class GameState :public State
{
public:
	GameState(GameDataReference data, std::string& p1, std::string& p2);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference data;

	Widgets* widget;

	sf::RectangleShape transitionShape;
	sf::Clock cleaningClock;
	bool screenCleaning = true;
	bool shapeDisappeared = false;
	bool shapeAppeared = true;

	std::vector<BoardSquare> boardSquares;
};