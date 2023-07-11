#pragma once
#include "State.h"
#include "Game.h"

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

};