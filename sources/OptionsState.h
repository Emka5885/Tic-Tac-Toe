#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"

class OptionsState :public State
{
public:
	OptionsState(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

private:
	GameDataReference data;

	sf::Text options;
	sf::Text optionsShadow;
	Button backButton;

	std::vector<std::pair<sf::RectangleShape, sf::Text>> grayRectangles;
	std::vector<sf::Text> textShadows;
};
