#include "InitialSetupState.h"

void InitialSetupState::Create()
{
	initialSetup.setString("Initial Setup");
	initialSetup.setCharacterSize(100);
	initialSetup.setFillColor(sf::Color::White);
	initialSetup.setOutlineColor(sf::Color::Black);
	initialSetup.setOutlineThickness(3);

	enterTextP1.setOutlineColor(sf::Color::Black);
	enterTextP1.setOutlineThickness(2);
	enterTextP1.setCharacterSize(25);

	p1Box.setOutlineColor(sf::Color::Black);
	p1Box.setOutlineThickness(4);
	p1Box.setSize({ TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y });
	p1Box.setOrigin(TEXT_BOX_SIZE_X / 2, TEXT_BOX_SIZE_Y / 2);

	blackLine.setSize({ 3, 50 });
	blackLine.setFillColor(sf::Color::Black);
	blackLine.setOrigin(blackLine.getSize().x / 2, blackLine.getSize().y / 2);

	messageP1.setString("maximum character length is 8");
	messageP1.setCharacterSize(15);
	messageP1.setFillColor(sf::Color::Red);
	messageP1.setOutlineColor(sf::Color::Black);
	messageP1.setOutlineThickness(1);
}

void InitialSetupState::ChangeP1Text()
{
	p1Text.setFillColor(sf::Color::Black);
	p1Text.setString(p1Input);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);
}

void InitialSetupState::DrawBlackLine()
{
	if (blackLineTimer.getElapsedTime().asSeconds() >= 0.5 && checkBlackLineTimer)
	{
		drawBlackLine = !drawBlackLine;
		blackLineTimer.restart();
	}
}
