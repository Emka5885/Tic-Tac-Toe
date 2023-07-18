#include "GameState.h"
#include "Definitions.h"

GameState::GameState(GameDataReference data, std::string p1, std::string p2) : data(data)
{
	widget = new Widgets(data->assets, p1, p2);
}

void GameState::Init()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BoardSquare boardSquare({ float(j) * 150 + 175, float(i) * 150 + 250 });
			boardSquares.emplace_back(boardSquare);
		}
	}

	disappearingShape.setFillColor(sf::Color({ 165, 165, 165 }));
	disappearingShape.setSize({ WIDTH, HEIGHT });
	disappearingShape.setOrigin(WIDTH / 2, HEIGHT / 2);
	disappearingShape.setPosition(WIDTH / 2, HEIGHT / 2);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			widget->ChangeTurn();
		}
	}
}

void GameState::Update()
{
	if (cleaningClock.getElapsedTime().asSeconds() >= 0.3 && screenCleaning)
	{
		if (disappearingShape.getSize().x < 25)
		{
			disappearingShape.setSize({ 0,0 });
			screenCleaning = false;
		}
		else
		{
			disappearingShape.setSize({ disappearingShape.getSize().x - 25, disappearingShape.getSize().y - 25 });
			disappearingShape.setOrigin(disappearingShape.getSize().x / 2, disappearingShape.getSize().y / 2);
		}
	}
}

void GameState::Draw()
{
	data->window.clear(sf::Color({ 165, 165, 165 }));

	widget->Draw(data->window);

	for (int i = 0; i < boardSquares.size(); i++)
	{
		boardSquares[i].Draw(data->window);
	}

	if (screenCleaning)
	{
		data->window.draw(disappearingShape);
	}

	data->window.display();
}
