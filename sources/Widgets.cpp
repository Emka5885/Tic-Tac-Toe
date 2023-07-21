#include "Widgets.h"
#include "Definitions.h"

Widgets::Widgets(AssetManager& assets, std::string p1, std::string p2) : assets(assets), p1(p1), p2(p2)
{
	Init();
}

Widgets::~Widgets()
{
}

void Widgets::Init()
{
	ChangeScore(0, 0);

	totalsText.setString("Game Totals");
	totalsText.setFont(assets.GetFont(defaultFont));
	totalsText.setCharacterSize(50);
	totalsText.setOrigin(totalsText.getGlobalBounds().width / 2, totalsText.getGlobalBounds().height / 2);
	totalsText.setPosition({ WIDTH / 2, 50 });
	totalsText.setOutlineColor(sf::Color::Black);
	totalsText.setOutlineThickness(2);
	totalsShadow = totalsText;
	totalsShadow.setFillColor(sf::Color::Black);
	totalsShadow.setPosition(totalsText.getPosition().x + 4, totalsText.getPosition().y + 3);

	turnText.setFont(assets.GetFont(defaultFont));
	turnText.setCharacterSize(70);
	turnText.setOutlineColor(sf::Color::Black);
	turnText.setOutlineThickness(4);
	turnShadow = turnText;
	turnShadow.setFillColor(sf::Color::Black);
	ChangeTurn();
	turnText.setPosition({ WIDTH / 2, 112 });
	turnShadow.setPosition(turnText.getPosition().x + 5, turnText.getPosition().y + 3);

	winText = turnText;
	winText.setString(p1 + " win!");
	winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
	winText.setPosition({ WIDTH / 2, 112 });
	winShadow = winText;
	winShadow.setOrigin(winShadow.getGlobalBounds().width / 2, winShadow.getGlobalBounds().height / 2);
	winShadow.setPosition(winText.getPosition().x + 5, winText.getPosition().y + 3);
	winShadow.setFillColor(sf::Color::Black);

	scoreDashText.setString(" - ");
	scoreDashText.setFont(assets.GetFont(defaultFont));
	scoreDashText.setCharacterSize(75);
	scoreDashText.setOrigin(scoreDashText.getGlobalBounds().width / 2, scoreDashText.getGlobalBounds().height / 2);
	scoreDashText.setPosition({ WIDTH / 2, SCORE_Y_POSITION });
	scoreDashText.setOutlineColor(sf::Color::Black);
	scoreDashText.setOutlineThickness(1);
	scoreP1Text = scoreDashText;
	scoreP1Text.setString(std::to_string(scoreP1));
	scoreP1Text.setOrigin(scoreP1Text.getGlobalBounds().width, scoreDashText.getGlobalBounds().height / 2);
	scoreP1Text.setPosition(WIDTH / 2 - scoreDashText.getGlobalBounds().width / 2, SCORE_Y_POSITION);
	scoreP2Text = scoreDashText;
	scoreP2Text.setString(std::to_string(scoreP2));
	scoreP2Text.setOrigin(0, scoreDashText.getGlobalBounds().height / 2);
	scoreP2Text.setPosition(WIDTH / 2 + scoreDashText.getGlobalBounds().width / 2, SCORE_Y_POSITION);

	pDashText.setString("   -   ");
	pDashText.setFont(assets.GetFont(defaultFont));
	pDashText.setCharacterSize(25);
	pDashText.setOrigin(pDashText.getGlobalBounds().width / 2, pDashText.getGlobalBounds().height / 2);
	pDashText.setPosition({ WIDTH / 2, PLAYER_Y_POSITION });
	pDashText.setOutlineColor(sf::Color::Black);
	pDashText.setOutlineThickness(2);
	pDashShadow = pDashText;
	pDashShadow.setFillColor(sf::Color::Black);
	pDashShadow.setPosition(pDashText.getPosition().x + 2, pDashText.getPosition().y + 2);

	p1Text = pDashText;
	p1Text.setString(p1);
	p1Text.setOrigin(p1Text.getGlobalBounds().width, pDashText.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 2 - pDashText.getGlobalBounds().width / 2, PLAYER_Y_POSITION);
	p1Shadow = p1Text;
	p1Shadow.setFillColor(sf::Color::Black);
	p1Shadow.setPosition(p1Text.getPosition().x + 2, p1Text.getPosition().y + 2);

	p2Text = pDashText;
	p2Text.setString(p2);
	p2Text.setOrigin(0, pDashText.getGlobalBounds().height / 2);
	p2Text.setPosition(WIDTH / 2 + pDashText.getGlobalBounds().width / 2, PLAYER_Y_POSITION);
	p2Shadow = p2Text;
	p2Shadow.setFillColor(sf::Color::Black);
	p2Shadow.setPosition(p2Text.getPosition().x + 2, p2Text.getPosition().y + 2);

	type = gameTotals;
}

void Widgets::ChangeScore(int scoreP1, int scoreP2)
{
	this->scoreP1 = scoreP1;
	this->scoreP2 = scoreP2;
}

void Widgets::ChangeTurn()
{
	if (type == turnP2)
	{
		turnText.setString(p1 + "'s turn");
		turnShadow.setString(p1 + "'s turn");
		turnText.setFillColor(sf::Color(225, 10, 90));
		type = turnP1;
	}
	else
	{
		turnText.setString(p2 + "'s turn");
		turnShadow.setString(p2 + "'s turn");
		turnText.setFillColor(sf::Color(50, 150, 225));
		type = turnP2;
	}

	turnText.setOrigin(turnText.getGlobalBounds().width / 2, turnText.getGlobalBounds().height / 2);
	turnShadow.setOrigin(turnShadow.getGlobalBounds().width / 2, turnShadow.getGlobalBounds().height / 2);
}

void Widgets::ChangeWidgetType()
{
	if (type == gameTotals)
	{
		if (rand() % 2)
		{
			type = turnP1;
			turnText.setString(p1 + "'s turn");
			turnShadow.setString(p1 + "'s turn");
			turnText.setFillColor(sf::Color(225, 10, 90));
		}
		else
		{
			type = turnP2;
			turnText.setString(p2 + "'s turn");
			turnShadow.setString(p2 + "'s turn");
			turnText.setFillColor(sf::Color(50,150,225));
		}
		turnText.setOrigin(turnText.getGlobalBounds().width / 2, turnText.getGlobalBounds().height / 2);
		turnShadow.setOrigin(turnShadow.getGlobalBounds().width / 2, turnShadow.getGlobalBounds().height / 2);
		isWinText = false;
	}
	else
	{
		type = gameTotals;
	}
}

void Widgets::Draw(sf::RenderWindow& window)
{
	if (type != gameTotals)
	{
		if (isWinText)
		{
			window.draw(winShadow);
			window.draw(winText);
		}
		else
		{
			window.draw(turnShadow);
			window.draw(turnText);
		}
	}
	else
	{
		window.draw(totalsShadow);
		window.draw(totalsText);

		window.draw(scoreP1Text);
		window.draw(scoreDashText);
		window.draw(scoreP2Text);

		window.draw(p1Shadow);
		window.draw(p1Text);
		window.draw(pDashShadow);
		window.draw(pDashText);
		window.draw(p2Shadow);
		window.draw(p2Text);
	}
}

void Widgets::ChangeText(GameTypes gameType)
{
	if (gameType == p1Wins)
	{
		winText.setString(p1 + " win!");
		winShadow.setString(p1 + " win!");
		winText.setFillColor(sf::Color(225, 10, 90));
	}
	else if (gameType == p2Wins)
	{
		winText.setString(p2 + " win!");
		winShadow.setString(p2 + " win!");
		winText.setFillColor(sf::Color(50, 150, 225));
	}
	else
	{
		winText.setString("Draw!");
		winShadow.setString("Draw!");
		winText.setFillColor(sf::Color::White);
	}

	winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
	winShadow.setOrigin(winShadow.getGlobalBounds().width / 2, winShadow.getGlobalBounds().height / 2);
	isWinText = true;
}

widgetTypes Widgets::GetWidgetType()
{
	return type;
}