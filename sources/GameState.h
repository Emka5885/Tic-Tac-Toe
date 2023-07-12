#pragma once
#include "State.h"
#include "Game.h"
#include "BoardSquare.h"
#include "Widgets.h"

class GameState :public State
{
public:
	GameState(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference data;

	Widgets* widget;

	std::vector<BoardSquare> boardSquares;
};