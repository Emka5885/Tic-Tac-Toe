#include "InitialSetupState2P.h"
#include "GameState.h"

InitialSetupState2P::InitialSetupState2P(GameDataReference data) : data(data)
{
}

void InitialSetupState2P::Init()
{
	Create();
	initialSetup.setFont(data->assets.GetFont(defaultFont));
	initialSetup.setOrigin(initialSetup.getGlobalBounds().width / 2, initialSetup.getGlobalBounds().height / 2);
	initialSetup.setPosition({ WIDTH / 2, 100 });
	initialSetupShadow = initialSetup;
	initialSetupShadow.setFillColor(sf::Color::Black);
	initialSetupShadow.setPosition({ WIDTH / 2 + 6, 105 });

	enterTextP1.setString("Enter new player 1 nickname:");
	enterTextP1.setFont(data->assets.GetFont(defaultFont));
	enterTextP1.setOrigin(enterTextP1.getGlobalBounds().width / 2, enterTextP1.getGlobalBounds().height / 2);
	enterTextP1.setPosition(WIDTH / 4, HEIGHT / 2 - TEXT_BOX_SIZE_Y - ENTER_BOX_OFFSET);
	enterTextP2 = enterTextP1;
	enterTextP2.setString("Enter new player 2 nickname:");
	enterTextP2.setOrigin(enterTextP2.getGlobalBounds().width / 2, enterTextP2.getGlobalBounds().height / 2);
	enterTextP2.setPosition(ENTER_BOX_2_POSITION_X, HEIGHT / 2 - TEXT_BOX_SIZE_Y - ENTER_BOX_OFFSET);

	p1Box.setPosition(WIDTH / 4, HEIGHT / 2 - ENTER_BOX_OFFSET);

	p2Box = p1Box;
	p2Box.setPosition(ENTER_BOX_2_POSITION_X, HEIGHT / 2 - ENTER_BOX_OFFSET);

	p1Text = sf::Text("Player 1", data->assets.GetFont(defaultFont), 40);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - p1Text.getGlobalBounds().height / 4 - ENTER_BOX_OFFSET);
	p1Text.setFillColor(sf::Color({ 120, 120, 120 }));

	p2Text = p1Text;
	p2Text.setString("Player 2");
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	p2Text.setPosition(ENTER_BOX_2_POSITION_X - 2, HEIGHT / 2 - p2Text.getGlobalBounds().height / 4 - ENTER_BOX_OFFSET);

	blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - ENTER_BOX_OFFSET);

	messageP1.setFont(data->assets.GetFont(defaultFont));
	messageP1.setOrigin(messageP1.getGlobalBounds().width / 2, messageP1.getGlobalBounds().height / 2);
	messageP1.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - 18);

	messageP2 = messageP1;
	messageP2.setPosition(ENTER_BOX_2_POSITION_X - 2, HEIGHT / 2 - 18);

	x_previewImage.setTexture(data->assets.GetTexture(xPreviewImage));
	x_previewImage.setSize({ 150, 150 });
	x_previewImage.setOrigin({ x_previewImage.getSize().x / 2 , x_previewImage.getSize().y / 2 });
	x_previewImage.setPosition({ WIDTH / 4, HEIGHT / 2 + ENTER_BOX_OFFSET });
	x_previewImage.setFillColor(sf::Color(xColor_r, xColor_g, xColor_b));

	o_previewImage.setTexture(data->assets.GetTexture(oPreviewImage));
	o_previewImage.setSize({ 150, 150 });
	o_previewImage.setOrigin({ o_previewImage.getSize().x / 2 , o_previewImage.getSize().y / 2 });
	o_previewImage.setPosition({ ENTER_BOX_2_POSITION_X, HEIGHT / 2 + ENTER_BOX_OFFSET });
	o_previewImage.setFillColor(sf::Color(oColor_r, oColor_g, oColor_b));

	sf::Text acceptText("Accept", data->assets.GetFont(defaultFont), 40);
	acceptText.setOutlineColor(sf::Color::Black);
	acceptText.setOutlineThickness(2);
	acceptButton = Button({ 200, 75 }, acceptText, sf::Color::Black, { WIDTH / 2, HEIGHT - 150 }, 10);

	CheckBoxClicked();
	sf::sleep(sf::seconds(0.2));
}

void InitialSetupState2P::HandleInput()
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
			if (event.key.code == sf::Mouse::Left)
			{
				CheckBoxClicked();
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
			p1String = p1Text.getString();
			p2String = p2Text.getString();
			data->machine.AddState(stateReference(new GameState(data, p1String, p2String)), true);
		}
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			CheckHovered();
		}
	}
}

void InitialSetupState2P::Update()
{
	DrawBlackLine();
}

void InitialSetupState2P::Draw()
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

	data->window.draw(x_previewImage);
	data->window.draw(o_previewImage);

	acceptButton.DrawButton(data->window);

	data->window.display();
}

void InitialSetupState2P::ChangeP2Text()
{
	p2Text.setFillColor(sf::Color::Black);
	p2Text.setString(p2Input);
	p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);
}

void InitialSetupState2P::CheckBoxClicked()
{
	checkBlackLineTimer = true;
	// p1Box
	if ((data->input.isButtonClicked(p1Box, sf::Mouse::Left, data->window)))
	{
		if (textBoxType != player1)
		{
			textBoxType = player1;
			blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);

			if (p2Input.getSize() <= 0)
			{
				p2Text.setString("Player 2");
				p2Text.setFillColor(sf::Color({ 120, 120, 120 }));
				p2Text.setOrigin(p2Text.getGlobalBounds().width / 2, p2Text.getGlobalBounds().height / 2);
			}
			if (p1Input.getSize() <= 0)
			{
				blackLine.setPosition(WIDTH / 4 - 2, HEIGHT / 2 - ENTER_BOX_OFFSET);
			}
		}
	}
	// p2Box
	else if ((data->input.isButtonClicked(p2Box, sf::Mouse::Left, data->window)))
	{
		if (textBoxType != player2)
		{
			textBoxType = player2;
			blackLine.setPosition(p2Text.getPosition().x + p2Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);

			if (p1Input.getSize() <= 0)
			{
				p1Text.setString("Player 1");
				p1Text.setFillColor(sf::Color({ 120, 120, 120 }));
				p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
			}
			if (p2Input.getSize() <= 0)
			{
				blackLine.setPosition(ENTER_BOX_2_POSITION_X - 2, HEIGHT / 2 - ENTER_BOX_OFFSET);
			}
		}
	}
	// none
	else
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

void InitialSetupState2P::CheckHovered()
{
	if (data->input.isButtonHovered(acceptButton.GetShape(), data->window) && (p1String.length() > 8 || p2String.length() > 8))
	{
		// accept button - move x
		if (data->input.GetMousePosition(data->window).x <= 275)
		{
			acceptButton.SetPosition({ float(data->input.GetMousePosition(data->window).x + ACCEPT_OFFSET),  acceptButton.GetShape().getPosition().y });
		}
		else if (data->input.GetMousePosition(data->window).x >= 525)
		{
			acceptButton.SetPosition({ float(data->input.GetMousePosition(data->window).x - ACCEPT_OFFSET),  acceptButton.GetShape().getPosition().y });
		}
		else
		{
			if (rand() % 2)
			{
				acceptButton.SetPosition({ float(data->input.GetMousePosition(data->window).x + ACCEPT_OFFSET),  acceptButton.GetShape().getPosition().y });
			}
			else
			{
				acceptButton.SetPosition({ float(data->input.GetMousePosition(data->window).x - ACCEPT_OFFSET),  acceptButton.GetShape().getPosition().y });
			}
		}
		// accept button - move y
		if (acceptButton.GetShape().getPosition().y < HEIGHT - ACCEPT_OFFSET)
		{
			acceptButton.SetPosition({ acceptButton.GetShape().getPosition().x,  HEIGHT - ENTER_BOX_OFFSET });
		}
		else if (acceptButton.GetShape().getPosition().y > HEIGHT - ENTER_BOX_OFFSET)
		{
			acceptButton.SetPosition({ acceptButton.GetShape().getPosition().x,  HEIGHT - ACCEPT_OFFSET });
		}
		else
		{
			if (rand() % 2)
			{
				acceptButton.SetPosition({ acceptButton.GetShape().getPosition().x,  float(data->input.GetMousePosition(data->window).y - 25) });
			}
			else
			{
				acceptButton.SetPosition({ acceptButton.GetShape().getPosition().x,  float(data->input.GetMousePosition(data->window).y + 25) });
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
