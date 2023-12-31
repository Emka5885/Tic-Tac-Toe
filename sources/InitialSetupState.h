#pragma once
#include "Button.h"
#include "Definitions.h"
#include "Game.h"

class InitialSetupState
{
public:
	void Create(GameDataReference& data);
	void ChangeP1Text();
	void DrawBlackLine();
	virtual void CheckAcceptButtonHovered(GameDataReference& data) = 0;

	virtual void CheckBoxClicked() = 0;

protected:
	sf::RectangleShape p1Box;
	sf::RectangleShape blackLine;
	Button acceptButton;

	sf::RectangleShape x_previewImage;
	sf::RectangleShape o_previewImage;

	sf::Clock blackLineTimer;
	bool drawBlackLine = true;
	bool checkBlackLineTimer = true;
	bool Backspace = false;

	std::string p1String;
	sf::String p1Input;
	sf::Text p1Text;
	sf::Text enterTextP1;
	sf::Text initialSetup, initialSetupShadow;
	sf::Text messageP1;
};
