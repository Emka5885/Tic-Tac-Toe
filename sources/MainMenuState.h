#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"

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

	bool quitt = false;

	sf::Text title;
	sf::Text titleShadow;
	Button playButton;
	Button optionsButton;
	Button quittButton;

	sf::Clock test;
};
