#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "ScrollBar.h"
#include "SwitchButton.h"

class OptionsState :public State
{
public:
	OptionsState(GameDataReference& data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

	void ChangeButtonsHoverd();
	void CheckButtonsClicked();

	void Save();

private:
	GameDataReference& data;

	sf::Text options;
	sf::Text optionsShadow;
	Button backButton;

	ScrollBar musicScrollBar, soundsScrollBar;
	SwitchButton musicOnSwitchButton, musicOffSwitchButton;
	SwitchButton soundsOnSwitchButton, soundsOffSwitchButton;
	SwitchButton onePSwitchButton, twoPSwitchButton;

	std::vector<std::pair<sf::RectangleShape, sf::Text>> grayRectangles;
	std::vector<sf::Text> textShadows;

	sf::RectangleShape coverMusic;
	sf::RectangleShape coverSounds;

	std::vector<std::pair<optionsTypes, int>> optionsFromFile;
};
