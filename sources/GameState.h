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

	void CheckBoardSquares_Clicked();
	void CheckToPlayOn();
	bool CheckWinCondition(boardTypes boardType);

private:
	GameDataReference data;

	GameTypes gameType = inProgress;

	sf::RectangleShape board;
	Widgets* widget;

	sf::RectangleShape transitionShape;
	sf::Clock cleaningClock;
	bool screenCleaning = true;
	bool shapeDisappeared = false;
	bool shapeAppeared = true;

	bool changeOfTurn = false;
	bool backToMainMenu = false;

	bool isSlantLine = false;

	std::vector<BoardSquare> boardSquares;

	sf::RectangleShape slantLine;
	sf::RectangleShape line;

	sf::Clock drawClock;
	sf::Clock winClock;
};