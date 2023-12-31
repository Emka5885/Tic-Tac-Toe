#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"

enum menuType { defaultMenu, play, options, quitt };
enum modeType { onePlayerType, twoPlayerType };

class MainMenuState :public State
{
public:
	MainMenuState(GameDataReference& data, bool startMusic = false);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference& data;

	sf::Text title;
	sf::Text titleShadow;
	Button playButton;
	Button optionsButton;
	Button quittButton;

	menuType type = defaultMenu;
	modeType mType = onePlayerType;
};
