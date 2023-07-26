#include "GameState.h"
#include "MainMenuState.h"
#include "Definitions.h"

GameState::GameState(GameDataReference data, std::string& p1, std::string& p2) : data(data)
{
	widget = new Widgets(data->assets, p1, p2);
}

void GameState::Init()
{
	board.setFillColor(sf::Color(200, 200, 200));
	board.setSize({ 474,474 });
	board.setPosition(163, 238);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BoardSquare boardSquare(data->assets, { float(j) * 158 + 242, float(i) * 158 + 317 });
			boardSquares.emplace_back(boardSquare);
		}
	}

	transitionShape.setFillColor(sf::Color({ 165, 165, 165 }));
	transitionShape.setSize({ WIDTH, HEIGHT });
	transitionShape.setOrigin(WIDTH / 2, HEIGHT / 2);
	transitionShape.setPosition(WIDTH / 2, HEIGHT / 2);

	slantLine.setFillColor(sf::Color(75, 75, 75, 0));
	slantLine.setOutlineColor(sf::Color(0,0,0,0));
	slantLine.setOutlineThickness(3);

	line = slantLine;
	line.setSize({ 458, 6 });
	line.setOrigin(line.getSize().x / 2, line.getSize().y / 2);
	line.setPosition(WIDTH / 2, HEIGHT / 2 + 75);

	slantLine.setSize({ float(458 * sqrt(2)), 6 });
	slantLine.setOrigin(slantLine.getSize().x / 2, slantLine.getSize().y / 2);
	slantLine.setPosition(WIDTH / 2, HEIGHT / 2 + 75);
	slantLine.rotate(45);

	sf::Text buttonsText("Next Round", data->assets.GetFont(defaultFont), 50);
	buttonsText.setFillColor(sf::Color(250, 250, 250));
	buttonsText.setOutlineColor(sf::Color::Black);
	buttonsText.setOutlineThickness(2);
	sf::Vector2f buttonsSize(324, 112);

	nextRoundButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, HEIGHT / 2 - 75 }, 10);

	buttonsText.setString("Main Menu");
	menuButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2,  HEIGHT / 2 + 90}, 10);

	buttonsText.setString("Quitt");
	quittButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2,  HEIGHT / 2 + 255 }, 10);
}

void GameState::HandleInput()
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
			CheckBoardSquares_Clicked();
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
				ClearScreen();
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
			if (backToMainMenu)
			{
				data->machine.RemoveState();
				data->machine.AddState(stateReference(new MainMenuState(data)), true);
			}
			else if (transitionShape.getSize().x < 25)
			{
				transitionShape.setSize({ 0,0 });
				screenCleaning = false;
				shapeDisappeared = true;
			}
			else
			{
				if (shapeAppeared)
				{
					shapeAppeared = false;
				}
				transitionShape.setSize({ transitionShape.getSize().x - 25, transitionShape.getSize().y - 25 });
				transitionShape.setOrigin(transitionShape.getSize().x / 2, transitionShape.getSize().y / 2);
			}
		}
	}

	if ((drawClock.getElapsedTime().asSeconds() >= 0.8 && gameType == draw) || (winClock.getElapsedTime().asSeconds() >= 1.5 && (gameType == p1Wins || gameType == p2Wins)))
	{
		screenCleaning = true;
	}

	CheckToPlayOn();
}

void GameState::Draw()
{
	data->window.clear(sf::Color({ 165, 165, 165 }));


	widget->Draw(data->window);

	if (widget->GetWidgetType() != gameTotals)
	{
		data->window.draw(board);

		for (int i = 0; i < boardSquares.size(); i++)
		{
			boardSquares[i].Draw(data->window);
		}
	}
	else
	{
		nextRoundButton.DrawButton(data->window);
		menuButton.DrawButton(data->window);
		quittButton.DrawButton(data->window);
	}

	if (gameType == p1Wins || gameType == p2Wins)
	{
		if (isSlantLine)
		{
			data->window.draw(slantLine);
		}
		else
		{
			data->window.draw(line);
		}
	}

	if (screenCleaning)
	{
		data->window.draw(transitionShape);
	}


	data->window.display();



	if (changeOfTurn)
	{
		changeOfTurn = false;
		sf::sleep(sf::seconds(0.5));
	}
}

void GameState::CheckBoardSquares_Clicked()
{
	for (int i = 0; i < boardSquares.size(); i++)
	{
		if (data->input.isButtonClicked(boardSquares[i].GetShape(), sf::Mouse::Left, data->window))
		{
			if (boardSquares[i].GetBoardType() == empty)
			{
				if (widget->GetWidgetType() == turnP1)
				{
					boardSquares[i].ChangeBoardType(x);
				}
				else
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

void GameState::CheckToPlayOn()
{
	if (gameType == inProgress)
	{
		if (!CheckWinCondition(x) && !CheckWinCondition(o))
		{
			gameType = draw;
			for (int i = 0; i < boardSquares.size(); i++)
			{
				if (boardSquares[i].GetBoardType() == empty)
				{
					gameType = inProgress;
					break;
				}
			}
		}
		drawClock.restart();
	}

	if (gameType != inProgress)
	{
		widget->ChangeText(gameType);

		if (gameType == draw)
		{
			int r = std::clamp(int(board.getFillColor().r - 1), 75, 200);

			if (drawClock.getElapsedTime().asSeconds() >= 0.005 && r > 75)
			{
				int g = std::clamp(int(board.getFillColor().g - 1), 75, 200);
				int b = std::clamp(int(board.getFillColor().b - 1), 75, 200);

				board.setFillColor(sf::Color(r, g, b));

				drawClock.restart();
			}
		}
		else
		{
			if (isSlantLine)
			{
				int a = std::clamp(int(slantLine.getFillColor().a + 4), 0, 255);
				if (winClock.getElapsedTime().asSeconds() >= 0.01 && a < 255)
				{
					slantLine.setFillColor({ slantLine.getFillColor().r, slantLine.getFillColor().g, slantLine.getFillColor().b, sf::Uint8(a) });
					slantLine.setOutlineColor({ 0, 0, 0, sf::Uint8(a) });
					winClock.restart();
				}
			}
			else
			{
				int a = std::clamp(int(line.getFillColor().a + 4), 0, 255);
				if (winClock.getElapsedTime().asSeconds() >= 0.01 && a < 255)
				{
					line.setFillColor({ line.getFillColor().r, line.getFillColor().g, line.getFillColor().b, sf::Uint8(a) });
					line.setOutlineColor({ 0, 0, 0, sf::Uint8(a) });
					winClock.restart();
				}
			}
		}
	}
}

bool GameState::CheckWinCondition(boardTypes boardType)
{
	bool win = false;

	for (int i = 0; i < 3; i++)
	{
		// horizontal
		int counter = 0;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i * 3 + j].GetBoardType() != boardType)
			{
				break;
			}
			counter++;
		}
		if (counter == 3)
		{
			line.setRotation(0);
			switch (i)
			{
			case 0:
				line.setPosition(WIDTH / 2, HEIGHT / 2 + 75 - 158);
				break;
			case 1:
				line.setPosition(WIDTH / 2, HEIGHT / 2 + 75);
				break;
			case 2:
				line.setPosition(WIDTH / 2, HEIGHT / 2 + 75 + 158);
				break;
			}

			win = true;
			break;
		}

		// vertically
		counter = 0;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i + j * 3].GetBoardType() != boardType)
			{
				break;
			}
			counter++;
		}
		if (counter == 3)
		{
			line.setRotation(90);
			switch (i)
			{
			case 0:
				line.setPosition(WIDTH / 2 - 158, HEIGHT / 2 + 75);
				break;
			case 1:
				line.setPosition(WIDTH / 2, HEIGHT / 2 + 75);
				break;
			case 2:
				line.setPosition(WIDTH / 2 + 158, HEIGHT / 2 + 75);
				break;
			}

			win = true;
			break;
		}
	}

	// slant
	if (boardSquares[0].GetBoardType() == boardType && boardSquares[4].GetBoardType() == boardType && boardSquares[8].GetBoardType() == boardType && !win)
	{
		slantLine.setRotation(45);
		isSlantLine = true;
		win = true;
	}
	else if (boardSquares[2].GetBoardType() == boardType && boardSquares[4].GetBoardType() == boardType && boardSquares[6].GetBoardType() == boardType && !win)
	{
		slantLine.setRotation(135);
		isSlantLine = true;
		win = true;
	}



	if (win)
	{
		if (boardType == x)
		{
			gameType = p1Wins;
		}
		else
		{
			gameType = p2Wins;
		}
		winClock.restart();
		return true;
	}

	return false;
}

void GameState::ClearScreen()
{
	nextRoundButton.Clicked(false);

	for (int i = 0; i < boardSquares.size(); i++)
	{
		boardSquares[i].ChangeBoardType(empty);
	}

	if (widget->GetWidgetType() != gameTotals && gameType == p1Wins)
	{
		widget->ChangeWidgetType(1, 0);
	}
	else if (widget->GetWidgetType() != gameTotals && gameType == p2Wins)
	{
		widget->ChangeWidgetType(0, 1);
	}
	else
	{
		widget->ChangeWidgetType();
	}

	gameType = inProgress;
	isSlantLine = false;
	slantLine.setFillColor(sf::Color(75, 75, 75, 0));
	slantLine.setOutlineColor(sf::Color(0, 0, 0, 0));
	line.setFillColor(sf::Color(75, 75, 75, 0));
	line.setOutlineColor(sf::Color(0, 0, 0, 0));
	board.setFillColor(sf::Color(200, 200, 200));
}
