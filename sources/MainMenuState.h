#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"

enum menuType { defaultMenu, play, options, quitt };

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

	sf::Text title;
	sf::Text titleShadow;
	Button playButton;
	Button optionsButton;
	Button quittButton;

	menuType type = defaultMenu;
};
