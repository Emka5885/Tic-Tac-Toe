#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Definitions.h"

class Widgets
{
private:
	sf::Text totalsText, totalsShadow;

	sf::Text scoreP1Text;
	sf::Text scoreDashText;
	sf::Text scoreP2Text;

	sf::Text pDashText, pDashShadow;
	sf::Text p1Text, p1Shadow;
	sf::Text p2Text, p2Shadow;

	sf::Text turnText;
	sf::Text turnShadow;

	sf::Text winText;
	sf::Text winShadow;

	std::string p1, p2;

	int scoreP1, scoreP2;
	widgetTypes type;

	bool isWinText = false;

	AssetManager& assets;

public:
	Widgets(AssetManager& assets, std::string p1 = "Player 1", std::string p2 = "Player 2");
	~Widgets();

	void Init();

	void ChangeScore(int scoreP1, int scoreP2);
	void ChangeTurn();
	void ChangeWidgetType();

	void Draw(sf::RenderWindow& window);
	void ChangeText(GameTypes gameType);

	widgetTypes GetWidgetType();
};