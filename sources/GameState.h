#pragma once
#include "BoardSquare.h"
#include "Widgets.h"
#include "Button.h"
#include "Game.h"

class GameState
{
public:
	void CheckBoardSquares_Clicked(GameDataReference& data);
	void CheckToPlayOn();
	bool CheckWinCondition(boardTypes boardType);

	void ClearScreen();

protected:
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

	Button menuButton;
	Button nextRoundButton;
	Button quittButton;
	bool quitt = false;
};