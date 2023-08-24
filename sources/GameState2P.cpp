#include "GameState2P.h"
#include "Definitions.h"

GameState2P::GameState2P(GameDataReference data, std::string& p1, std::string& p2) : data(data)
{
	widget = new Widgets(data->assets, p1, p2);
}

void GameState2P::Init()
{
	InitGameState(data);
}

void GameState2P::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || quitt)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			screenCleaning = true;
			backToMainMenu = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameType == inProgress && widget->GetWidgetType() != gameTotals)
		{
			CheckBoardSquares_Clicked(data);
		}

		if (widget->GetWidgetType() == gameTotals && !screenCleaning)
		{
			// clicked
			if (data->input.isButtonClicked(quittButton.GetShape(), sf::Mouse::Left, data->window))
			{
				quittButton.Clicked();
				quitt = true;
			}
			else if (data->input.isButtonClicked(nextRoundButton.GetShape(), sf::Mouse::Left, data->window))
			{
				nextRoundButton.Clicked();
				screenCleaning = true;
			}
			else if (data->input.isButtonClicked(menuButton.GetShape(), sf::Mouse::Left, data->window))
			{
				menuButton.Clicked();
				screenCleaning = true;
				backToMainMenu = true;
			}
			// hovered
			if (event.type == sf::Event::MouseMoved)
			{
				if (data->input.isButtonHovered(nextRoundButton.GetShape(), data->window))
				{
					nextRoundButton.ChangeHover(true);
				}
				else
				{
					nextRoundButton.ChangeHover(false);
				}

				if (data->input.isButtonHovered(menuButton.GetShape(), data->window))
				{
					menuButton.ChangeHover(true);
				}
				else
				{
					menuButton.ChangeHover(false);
				}

				if (data->input.isButtonHovered(quittButton.GetShape(), data->window))
				{
					quittButton.ChangeHover(true);
				}
				else
				{
					quittButton.ChangeHover(false);
				}
			}
		}
	}
}

void GameState2P::Update()
{
	UpdateGameState(data);
}

void GameState2P::Draw()
{
	DrawGameState(data);
}