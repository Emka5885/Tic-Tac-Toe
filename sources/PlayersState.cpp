#include "PlayersState.h"
#include "Definitions.h"

PlayersState::PlayersState(GameDataReference data) : data(data)
{
}

void PlayersState::Init()
{
	p1Box.setSize({ TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y });
	p1Box.setOrigin(TEXT_BOX_SIZE_X / 2, TEXT_BOX_SIZE_Y / 2);
	p1Box.setPosition(WIDTH / 4, HEIGHT / 2);
	p1Box.setOutlineColor(sf::Color::Black);
	p1Box.setOutlineThickness(4);

	p2Box = p1Box;
	p2Box.setPosition(WIDTH / 2 + WIDTH / 4, HEIGHT / 2);

	p1Text.setString("Player 1");
	p1Text.setFont(data->assets.GetFont(defaultFont));
	p1Text.setCharacterSize(40);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - p1Text.getGlobalBounds().height / 4);
	p1Text.setFillColor(sf::Color({ 120, 120, 120 }));

	p2Text = p1Text;
	p2Text.setString("Player 2");
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	p2Text.setPosition(WIDTH / 2 + WIDTH / 4 - 2, HEIGHT / 2 - p2Text.getGlobalBounds().height / 4);

	blackLine.setSize({ 3, 50 });
	blackLine.setFillColor(sf::Color::Black);
	blackLine.setOrigin(blackLine.getSize().x / 2, blackLine.getSize().y / 2);
	blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2);
}

void PlayersState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		//check which text box was clicked
		if (event.type == sf::Event::MouseButtonPressed)
		{
			checkBlackLineTimer = true;
			//p1Box
			if ((data->input.isButtonClicked(p1Box, sf::Mouse::Left, data->window)))
			{
				if (textBoxType != 1)
				{
					textBoxType = player1;
					blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2);

					if (p2Input.getSize() <= 0)
					{
						p2Text.setString("Player 2");
						p2Text.setFillColor(sf::Color({ 120, 120, 120 }));
						p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
					}
					if (p1Input.getSize() <= 0)
					{
						blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2);
					}
				}
			}
			//p2Box
			else if ((data->input.isButtonClicked(p2Box, sf::Mouse::Left, data->window)))
			{
				if (textBoxType != 2)
				{
					textBoxType = player2;
					blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2);

					if (p1Input.getSize() <= 0)
					{
						p1Text.setString("Player 1");
						p1Text.setFillColor(sf::Color({ 120, 120, 120 }));
						p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
					}
					if (p2Input.getSize() <= 0)
					{
						blackLine.setPosition(WIDTH / 2 + WIDTH / 4 - 2, HEIGHT / 2);
					}
				}
			}
			//none
			else if (event.key.code == sf::Mouse::Left)
			{
				textBoxType = none;
				checkBlackLineTimer = false;
				drawBlackLine = false;

				if (p1Input.getSize() <= 0)
				{
					p1Text.setString("Player 1");
					p1Text.setFillColor(sf::Color({ 120, 120, 120 }));
					p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
				}
				if (p2Input.getSize() <= 0)
				{
					p2Text.setString("Player 2");
					p2Text.setFillColor(sf::Color({ 120, 120, 120 }));
					p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
				}
			}
		}
		//check text box type
		if (textBoxType == 1)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (p1String.length() > 12)
					{
						p1String.erase(p1String.length() - 1, 1);
						p1Input = p1String.substr(p1String.length() - 12, p1String.length());
						ChangeP1Text();
					}
					else if (p1Input.getSize() > 0)
					{
						p1String.erase(p1String.length() - 1, 1);
						p1Input = p1String;
						ChangeP1Text();
					}
					Backspace = true;
				}
			}
			
			if (event.type == sf::Event::TextEntered && !Backspace)
			{
				if (event.text.unicode < 128 && p1Input.getSize() < 12)
				{
					p1String += event.text.unicode;
					p1Input += event.text.unicode;
					ChangeP1Text();
				}
				else if (event.text.unicode < 128)
				{
					p1String += event.text.unicode;
					p1Input = p1String.substr(p1String.length() - 12, p1String.length());
					ChangeP1Text();
				}
			}
		}
		else if (textBoxType == 2)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (p2String.length() > 12)
					{
						p2String.erase(p2String.length() - 1, 1);
						p2Input = p2String.substr(p2String.length() - 12, p2String.length());
						ChangeP2Text();
					}
					else if (p2Input.getSize() > 0)
					{
						p2String.erase(p2String.length() - 1, 1);
						p2Input = p2String;
						ChangeP2Text();
					}
					Backspace = true;
				}
			}

			if (event.type == sf::Event::TextEntered && !Backspace)
			{
				if (event.text.unicode < 128 && p2Input.getSize() < 12)
				{
					p2String += event.text.unicode;
					p2Input += event.text.unicode;
					ChangeP2Text();
				}
				else if (event.text.unicode < 128)
				{
					p2String += event.text.unicode;
					p2Input = p2String.substr(p2String.length() - 12, p2String.length());
					ChangeP2Text();
				}
			}
		}
		//if backspace has been released
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				Backspace = false;
			}
		}
	}
}

void PlayersState::Update()
{
	if (blackLineTimer.getElapsedTime().asSeconds() >= 0.5 && checkBlackLineTimer)
	{
		drawBlackLine = !drawBlackLine;
		blackLineTimer.restart();
	}
}

void PlayersState::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.draw(p1Box);
	data->window.draw(p1Text);
	data->window.draw(p2Box);
	data->window.draw(p2Text);

	if (drawBlackLine)
	{
		data->window.draw(blackLine);
	}

	data->window.display();
}

void PlayersState::ChangeP1Text()
{
	p1Text.setFillColor(sf::Color::Black);
	p1Text.setString(p1Input);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2);
}

void PlayersState::ChangeP2Text()
{
	p2Text.setFillColor(sf::Color::Black);
	p2Text.setString(p2Input);
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2);
}
