#include "GameState.h"
#include "Definitions.h"

GameState::GameState(GameDataReference data, std::string& p1, std::string& p2) : data(data)
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

	transitionShape.setFillColor(sf::Color({ 165, 165, 165 }));
	transitionShape.setSize({ WIDTH, HEIGHT });
	transitionShape.setOrigin(WIDTH / 2, HEIGHT / 2);
	transitionShape.setPosition(WIDTH / 2, HEIGHT / 2);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			//widget->ChangeTurn();
			if (!screenCleaning)
			{
				screenCleaning = true;
			}
		}
	}
}

void GameState::Update()
{
	// transition
	if (cleaningClock.getElapsedTime().asSeconds() >= 0.3 && screenCleaning)
	{
		// appearance
		if (shapeDisappeared)
		{
			if (transitionShape.getSize().x > WIDTH - 25)
			{
				transitionShape.setSize({ WIDTH, HEIGHT });
				transitionShape.setOrigin(WIDTH / 2, HEIGHT / 2);
				shapeDisappeared = false;
				shapeAppeared = true;
			}
			else
			{
				transitionShape.setSize({ transitionShape.getSize().x + 25, transitionShape.getSize().y + 25 });
				transitionShape.setOrigin(transitionShape.getSize().x / 2, transitionShape.getSize().y / 2);
			}
		}
		// disappearance
		else
		{
			if (transitionShape.getSize().x < 25)
			{
				transitionShape.setSize({ 0,0 });
				screenCleaning = false;
				shapeDisappeared = true;
			}
			else
			{
				if (shapeAppeared)
				{
					widget->ChangeWidgetType();
					shapeAppeared = false;
				}
				transitionShape.setSize({ transitionShape.getSize().x - 25, transitionShape.getSize().y - 25 });
				transitionShape.setOrigin(transitionShape.getSize().x / 2, transitionShape.getSize().y / 2);
			}
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
		data->window.draw(transitionShape);
	}

	data->window.display();
}
