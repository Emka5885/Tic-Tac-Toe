#pragma once
#include "State.h"
#include "Game.h"

class MainMenuState :public State
{
public:
	MainMenuState(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference data;

};
