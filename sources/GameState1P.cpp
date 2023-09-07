#include "GameState1P.h"

GameState1P::GameState1P(GameDataReference& data, std::string& player, bool FirstPlayerPlaysX) : data(data), FirstPlayerPlaysX(FirstPlayerPlaysX)
{
	widget = new Widgets(data->assets, player, "Computer", FirstPlayerPlaysX);
	computer = new Computer(FirstPlayerPlaysX);
}

void GameState1P::Init()
{
	InitGameState(data, FirstPlayerPlaysX);
	startClock.restart();
}

void GameState1P::HandleInput()
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameType == inProgress && widget->GetWidgetType() != gameTotals && widget->GetWidgetType() == turnP1)
		{
			CheckBoardSquares_Clicked();
			waitClock.restart();
		}

		if (widget->GetWidgetType() == gameTotals && !screenCleaning)
		{
			// clicked
			if (data->input.isButtonClicked(quittButton.GetShape(), sf::Mouse::Left, data->window))
			{
				quittButton.Clicked();
				quitt = true;
				data->gameAudio.PlaySound();
			}
			else if (data->input.isButtonClicked(nextRoundButton.GetShape(), sf::Mouse::Left, data->window))
			{
				nextRoundButton.Clicked();
				screenCleaning = true;
				data->gameAudio.PlaySound();
			}
			else if (data->input.isButtonClicked(menuButton.GetShape(), sf::Mouse::Left, data->window))
			{
				menuButton.Clicked();
				screenCleaning = true;
				backToMainMenu = true;
				data->gameAudio.PlaySound();
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

void GameState1P::Update()
{
	UpdateGameState(data);

	if (screenCleaning)
	{
		start = true;
		startClock.restart();
	}
	else
	{
		if (widget->GetWidgetType() == turnP1)
		{
			start = false;
		}

		if (gameType == inProgress && widget->GetWidgetType() != gameTotals && widget->GetWidgetType() == turnP2)
		{
			if (startClock.getElapsedTime().asSeconds() >= 1.5 && start)
			{
				computer.SelectSquare(boardSquares);

				SetComputerSelection();
			}
			else if (!start && waitClock.getElapsedTime().asSeconds() >= 1.5)
			{
				computer.SelectSquare(boardSquares);

				SetComputerSelection();
			}
		}
	}
}

void GameState1P::Draw()
{
	DrawGameState(data);
}

void GameState1P::CheckBoardSquares_Clicked()
{
	for (int i = 0; i < boardSquares.size(); i++)
	{
		if (data->input.isButtonClicked(boardSquares[i].GetShape(), sf::Mouse::Left, data->window))
		{
			if (boardSquares[i].GetBoardType() == empty)
			{
				if (widget->GetWidgetType() == turnP1 && FirstPlayerPlaysX)
				{
					boardSquares[i].ChangeBoardType(x);
				}
				else if (widget->GetWidgetType() == turnP1)
				{
					boardSquares[i].ChangeBoardType(o);
				}
				widget->ChangeTurn();
				changeOfTurn = true;
			}
			break;
		}
	}
}

void GameState1P::SetComputerSelection()
{
	for (int i = 0; i < boardSquares.size(); i++)
	{
		if (computer.GetComputerOption() == i && !FirstPlayerPlaysX)
		{
			boardSquares[i].ChangeBoardType(x);
		}
		else if(computer.GetComputerOption() == i && FirstPlayerPlaysX)
		{
			boardSquares[i].ChangeBoardType(o);
		}
	}
	widget->ChangeTurn();
	changeOfTurn = true;

	CheckToPlayOn();
}
