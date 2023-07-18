#include "InitialSetupState.h"
#include "GameState.h"
#include "Definitions.h"

InitialSetupState::InitialSetupState(GameDataReference data) : data(data)
{
}

void InitialSetupState::Init()
{
	initialSetup = sf::Text("Initial Setup", data->assets.GetFont(defaultFont), 100);
	initialSetup.setOrigin(initialSetup.getGlobalBounds().width / 2, initialSetup.getGlobalBounds().height / 2);
	initialSetup.setPosition({ WIDTH / 2, 100 });
	initialSetup.setFillColor(sf::Color::White);
	initialSetup.setOutlineColor(sf::Color::Black);
	initialSetup.setOutlineThickness(3);
	initialSetupShadow = initialSetup;
	initialSetupShadow.setFillColor(sf::Color::Black);
	initialSetupShadow.setPosition({ WIDTH / 2 + 6, 105 });

	enterTextP1 = sf::Text("Enter new player 1 nickname:", data->assets.GetFont(defaultFont), 20);
	enterTextP1.setOutlineColor(sf::Color::Black);
	enterTextP1.setOutlineThickness(2);
	enterTextP1.setOrigin(enterTextP1.getGlobalBounds().width / 2, enterTextP1.getGlobalBounds().height / 2);
	enterTextP1.setPosition(WIDTH / 4, HEIGHT / 2 - TEXT_BOX_SIZE_Y - 50);
	enterTextP2 = enterTextP1;
	enterTextP2.setString("Enter new player 2 nickname:");
	enterTextP2.setOrigin(enterTextP2.getGlobalBounds().width / 2, enterTextP2.getGlobalBounds().height / 2);
	enterTextP2.setPosition(WIDTH / 2 + WIDTH / 4, HEIGHT / 2 - TEXT_BOX_SIZE_Y - 50);

	p1Box.setSize({ TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y });
	p1Box.setOrigin(TEXT_BOX_SIZE_X / 2, TEXT_BOX_SIZE_Y / 2);
	p1Box.setPosition(WIDTH / 4, HEIGHT / 2 - 50);
	p1Box.setOutlineColor(sf::Color::Black);
	p1Box.setOutlineThickness(4);

	p2Box = p1Box;
	p2Box.setPosition(WIDTH / 2 + WIDTH / 4, HEIGHT / 2 - 50);

	p1Text = sf::Text("Player 1", data->assets.GetFont(defaultFont), 40);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - p1Text.getGlobalBounds().height / 4 - 50);
	p1Text.setFillColor(sf::Color({ 120, 120, 120 }));

	p2Text = p1Text;
	p2Text.setString("Player 2");
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	p2Text.setPosition(WIDTH / 2 + WIDTH / 4 - 2, HEIGHT / 2 - p2Text.getGlobalBounds().height / 4 - 50);

	blackLine.setSize({ 3, 50 });
	blackLine.setFillColor(sf::Color::Black);
	blackLine.setOrigin(blackLine.getSize().x / 2, blackLine.getSize().y / 2);
	blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - 50);

	messageP1 = sf::Text("maximum character length is 8", data->assets.GetFont(defaultFont), 15);
	messageP1.setOrigin(messageP1.getGlobalBounds().width / 2, messageP1.getGlobalBounds().height / 2);
	messageP1.setPosition(WIDTH / 4 - 2, HEIGHT / 2 + 10);
	messageP1.setFillColor(sf::Color::Red);
	messageP1.setOutlineColor(sf::Color::Black);
	messageP1.setOutlineThickness(1);

	messageP2 = messageP1;
	messageP2.setPosition(WIDTH / 2 + WIDTH / 4 - 2, HEIGHT / 2 + 10);

	x.first = 1;
	x.second.setTexture(data->assets.GetTexture("x"));
	x.second.setSize({ 100, 100 });
	x.second.setOrigin({ x.second.getSize().x / 2 , x.second.getSize().y / 2 });
	x.second.setPosition({ WIDTH / 4, HEIGHT / 2 + 100 });

	o.first = 2;
	o.second.setTexture(data->assets.GetTexture("o"));
	o.second.setSize({ 100, 100 });
	o.second.setOrigin({ o.second.getSize().x / 2 , o.second.getSize().y / 2});
	o.second.setPosition({ WIDTH / 2 + WIDTH / 4, HEIGHT / 2 + 100 });

	sf::Text acceptText("Accept", data->assets.GetFont(defaultFont), 40);
	acceptText.setOutlineColor(sf::Color::Black);
	acceptText.setOutlineThickness(2);
	acceptButton = Button({ 200, 75 }, acceptText, sf::Color::Black, { WIDTH / 2, HEIGHT - 150 }, 10);
}

void InitialSetupState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		// check which text box was clicked
		if (event.type == sf::Event::MouseButtonPressed)
		{
			checkBlackLineTimer = true;
			// p1Box
			if ((data->input.isButtonClicked(p1Box, sf::Mouse::Left, data->window)))
			{
				if (textBoxType != 1)
				{
					textBoxType = player1;
					blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - 50);

					if (p2Input.getSize() <= 0)
					{
						p2Text.setString("Player 2");
						p2Text.setFillColor(sf::Color({ 120, 120, 120 }));
						p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
					}
					if (p1Input.getSize() <= 0)
					{
						blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - 50);
					}
				}
			}
			// p2Box
			else if ((data->input.isButtonClicked(p2Box, sf::Mouse::Left, data->window)))
			{
				if (textBoxType != 2)
				{
					textBoxType = player2;
					blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - 50);

					if (p1Input.getSize() <= 0)
					{
						p1Text.setString("Player 1");
						p1Text.setFillColor(sf::Color({ 120, 120, 120 }));
						p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
					}
					if (p2Input.getSize() <= 0)
					{
						blackLine.setPosition(WIDTH / 2 + WIDTH / 4 - 2, HEIGHT / 2 - 50);
					}
				}
			}
			// none
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
		// check text box type
		if (textBoxType == 1)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (p1String.length() > 8)
					{
						p1String.erase(p1String.length() - 1, 1);
						p1Input = p1String.substr(p1String.length() - 8, p1String.length());
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
				if (event.text.unicode < 128 && p1Input.getSize() < 8)
				{
					p1String += event.text.unicode;
					p1Input += event.text.unicode;
					ChangeP1Text();
				}
				else if (event.text.unicode < 128)
				{
					p1String += event.text.unicode;
					p1Input = p1String.substr(p1String.length() - 8, p1String.length());
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
					if (p2String.length() > 8)
					{
						p2String.erase(p2String.length() - 1, 1);
						p2Input = p2String.substr(p2String.length() - 8, p2String.length());
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
				if (event.text.unicode < 128 && p2Input.getSize() < 8)
				{
					p2String += event.text.unicode;
					p2Input += event.text.unicode;
					ChangeP2Text();
				}
				else if (event.text.unicode < 128)
				{
					p2String += event.text.unicode;
					p2Input = p2String.substr(p2String.length() - 8, p2String.length());
					ChangeP2Text();
				}
			}
		}
		// if backspace has been released
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				Backspace = false;
			}
		}
		// clicked
		if (data->input.isButtonClicked(acceptButton.GetShape(), sf::Mouse::Left, data->window) && p1String.length() <= 8 && p2String.length() <= 8)
		{
			acceptButton.Clicked();
			sf::sleep(sf::seconds(1));
			data->machine.RemoveState();
			data->machine.AddState(stateReference(new GameState(data, p1Text.getString(), p2Text.getString())), true);
		}
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			if (data->input.isButtonHovered(acceptButton.GetShape(), data->window) && (p1String.length() > 8 || p2String.length() > 8))
			{
				if (data->input.GetMousePosition(data->window).x <= 275)
				{
					acceptButton.SetShapePosition({ float(data->input.GetMousePosition(data->window).x + 200),  acceptButton.GetShape().getPosition().y });
				}
				else if(data->input.GetMousePosition(data->window).x >= 525)
				{
					acceptButton.SetShapePosition({ float(data->input.GetMousePosition(data->window).x - 200),  acceptButton.GetShape().getPosition().y });
				}
				else
				{
					if (rand() % 2)
					{
						acceptButton.SetShapePosition({ float(data->input.GetMousePosition(data->window).x + 200),  acceptButton.GetShape().getPosition().y });
					}
					else
					{
						acceptButton.SetShapePosition({ float(data->input.GetMousePosition(data->window).x - 200),  acceptButton.GetShape().getPosition().y });
					}
				}

				if (acceptButton.GetShape().getPosition().y < HEIGHT - 200)
				{
					acceptButton.SetShapePosition({ acceptButton.GetShape().getPosition().x,  HEIGHT - 75 });
				}
				else if(acceptButton.GetShape().getPosition().y > HEIGHT - 75)
				{
					acceptButton.SetShapePosition({ acceptButton.GetShape().getPosition().x,  HEIGHT - 200 });
				}
				else
				{
					if (rand() % 2)
					{
						acceptButton.SetShapePosition({ acceptButton.GetShape().getPosition().x,  float(data->input.GetMousePosition(data->window).y - 25) });
					}
					else
					{
						acceptButton.SetShapePosition({ acceptButton.GetShape().getPosition().x,  float(data->input.GetMousePosition(data->window).y + 25) });
					}
				}
			}
			else
			{
				if (data->input.isButtonHovered(acceptButton.GetShape(), data->window))
				{
					acceptButton.ChangeHover(true);
				}
				else
				{
					acceptButton.ChangeHover(false);
				}
			}
		}
	}
}

void InitialSetupState::Update()
{
	if (blackLineTimer.getElapsedTime().asSeconds() >= 0.5 && checkBlackLineTimer)
	{
		drawBlackLine = !drawBlackLine;
		blackLineTimer.restart();
	}
}

void InitialSetupState::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.draw(initialSetupShadow);
	data->window.draw(initialSetup);
	data->window.draw(enterTextP1);
	data->window.draw(p1Box);
	data->window.draw(p1Text);
	data->window.draw(enterTextP2);
	data->window.draw(p2Box);
	data->window.draw(p2Text);

	if (p1String.length() > 8)
	{
		data->window.draw(messageP1);
	}
	
	if (p2String.length() > 8)
	{
		data->window.draw(messageP2);
	}

	if (drawBlackLine)
	{
		data->window.draw(blackLine);
	}

	data->window.draw(x.second);
	data->window.draw(o.second);

	acceptButton.DrawButton(data->window);

	data->window.display();
}

void InitialSetupState::ChangeP1Text()
{
	p1Text.setFillColor(sf::Color::Black);
	p1Text.setString(p1Input);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - 50);
}

void InitialSetupState::ChangeP2Text()
{
	p2Text.setFillColor(sf::Color::Black);
	p2Text.setString(p2Input);
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - 50);
}
