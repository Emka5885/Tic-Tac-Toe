#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"

enum textBoxTypes {none, player1, player2};

class InitialSetupState :public State
{
public:
	InitialSetupState(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

	void ChangeP1Text();
	void ChangeP2Text();

	void CheckBoxClicked();
	void CheckHovered();

private:
	GameDataReference data;

	sf::RectangleShape p1Box, p2Box;
	sf::RectangleShape blackLine;
	Button acceptButton;

	sf::RectangleShape x_previewImage;
	sf::RectangleShape o_previewImage;

	sf::Clock blackLineTimer;
	bool drawBlackLine = true;
	bool checkBlackLineTimer = true;
	bool Backspace = false;

	std::string p1String, p2String;
	sf::String p1Input, p2Input;
	sf::Text p1Text, p2Text;
	sf::Text enterTextP1, enterTextP2;
	sf::Text initialSetup, initialSetupShadow;
	sf::Text messageP1, messageP2;

	textBoxTypes textBoxType = player1;
};
