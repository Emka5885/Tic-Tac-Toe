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
	totalsText.setPosition({ WIDTH / 2, 50 });
	totalsText.setOutlineColor(sf::Color::Black);
	totalsText.setOutlineThickness(2);
	totalsShadow = totalsText;
	totalsShadow.setFillColor(sf::Color::Black);
	totalsShadow.setPosition(totalsText.getPosition().x + 4, totalsText.getPosition().y + 3);

	scoreText.setString("0 - 0");
	scoreText.setFont(assets.GetFont(defaultFont));
	scoreText.setCharacterSize(75);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition({ WIDTH / 2, 120 });

	pDashText.setString("   -   ");
	pDashText.setFont(assets.GetFont(defaultFont));
	pDashText.setCharacterSize(25);
	pDashText.setOrigin(pDashText.getGlobalBounds().width / 2, pDashText.getGlobalBounds().height / 2);
	pDashText.setPosition({ WIDTH / 2, 200 });
	pDashText.setOutlineColor(sf::Color::Black);
	pDashText.setOutlineThickness(2);
	pDashShadow = pDashText;
	pDashShadow.setFillColor(sf::Color::Black);
	pDashShadow.setPosition(pDashText.getPosition().x + 2, pDashText.getPosition().y + 2);

	p1Text = pDashText;
	p1Text.setString(p1);
	p1Text.setOrigin(p1Text.getGlobalBounds().width, pDashText.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 2 - pDashText.getGlobalBounds().width / 2, 200);
	p1Shadow = p1Text;
	p1Shadow.setFillColor(sf::Color::Black);
	p1Shadow.setPosition(p1Text.getPosition().x + 2, p1Text.getPosition().y + 2);

	p2Text = pDashText;
	p2Text.setString(p2);
	p2Text.setOrigin(0, pDashText.getGlobalBounds().height / 2);
	p2Text.setPosition(WIDTH / 2 + pDashText.getGlobalBounds().width / 2, 200);
	p2Shadow = p2Text;
	p2Shadow.setFillColor(sf::Color::Black);
	p2Shadow.setPosition(p2Text.getPosition().x + 2, p2Text.getPosition().y + 2);
}

void Widgets::Draw(sf::RenderWindow& window)
{
	window.draw(totalsShadow);
	window.draw(totalsText);

	window.draw(scoreText);

	window.draw(p1Shadow);
	window.draw(p1Text);
	window.draw(pDashShadow);
	window.draw(pDashText);
	window.draw(p2Shadow);
	window.draw(p2Text);
}
