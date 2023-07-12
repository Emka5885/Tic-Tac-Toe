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
	totalsText.setString("Game Totals");
	totalsText.setFont(assets.GetFont(defaultFont));
	totalsText.setCharacterSize(50);
	totalsText.setOrigin(totalsText.getGlobalBounds().width / 2, totalsText.getGlobalBounds().height / 2);
	totalsText.setPosition({ WIDTH / 2 - 100, 100 });

	scoreText.setString("0 - 0");
	scoreText.setFont(assets.GetFont(defaultFont));
	scoreText.setCharacterSize(75);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition({ WIDTH / 2, 100 });

	playersText.setString(p1 + " - " + p2);
	playersText.setFont(assets.GetFont(defaultFont));
	playersText.setCharacterSize(50);
	playersText.setOrigin(playersText.getGlobalBounds().width / 2, playersText.getGlobalBounds().height / 2);
	playersText.setPosition({ WIDTH / 2 + 100, 100 });
}

void Widgets::Draw(sf::RenderWindow& window)
{
	window.draw(totalsText);
	window.draw(scoreText);
	window.draw(playersText);
}
