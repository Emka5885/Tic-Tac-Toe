#include "GameState.h"
#include "Definitions.h"

GameState::GameState(GameDataReference data) : data(data)
{
	widget = new Widgets(data->assets);
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
}

void GameState::Draw()
{
	data->window.clear(sf::Color({ 165, 165, 165 }));

	widget->Draw(data->window);

	for (int i = 0; i < boardSquares.size(); i++)
	{
		boardSquares[i].Draw(data->window);
	}

	data->window.display();
}
