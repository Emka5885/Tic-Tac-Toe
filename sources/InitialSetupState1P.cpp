#include "InitialSetupState1P.h"
#include "GameState1P.h"

InitialSetupState1P::InitialSetupState1P(GameDataReference data) : data(data)
{
}

void InitialSetupState1P::Init()
{
	Create();
	initialSetup.setFont(data->assets.GetFont(defaultFont));
	initialSetup.setOrigin(initialSetup.getGlobalBounds().width / 2, initialSetup.getGlobalBounds().height / 2);
	initialSetup.setPosition({ WIDTH / 2, 100 });
	initialSetupShadow = initialSetup;
	initialSetupShadow.setFillColor(sf::Color::Black);
	initialSetupShadow.setPosition({ WIDTH / 2 + 6, 105 });

	enterTextP1.setString("Enter new player nickname:");
	enterTextP1.setFont(data->assets.GetFont(defaultFont));
	enterTextP1.setOrigin(enterTextP1.getGlobalBounds().width / 2, enterTextP1.getGlobalBounds().height / 2);
	enterTextP1.setPosition(WIDTH / 2, HEIGHT / 2 - TEXT_BOX_SIZE_Y - ENTER_BOX_OFFSET);

	p1Box.setPosition(WIDTH / 2, HEIGHT / 2 - ENTER_BOX_OFFSET);

	p1Text = sf::Text("Player", data->assets.GetFont(defaultFont), 40);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	p1Text.setPosition(WIDTH / 2 - 2, HEIGHT / 2 - p1Text.getGlobalBounds().height / 4 - ENTER_BOX_OFFSET);
	p1Text.setFillColor(sf::Color({ 120, 120, 120 }));

	messageP1.setFont(data->assets.GetFont(defaultFont));
	messageP1.setOrigin(messageP1.getGlobalBounds().width / 2, messageP1.getGlobalBounds().height / 2);
	messageP1.setPosition(WIDTH / 2 - 2, HEIGHT / 2 - 18);

	if (rand() % 2 == 0)
	{
		playerType = xPlayer;
	}
	else
	{
		playerType = oPlayer;
	}

	x_previewImage.setTexture(data->assets.GetTexture(xPreviewImage));
	x_previewImage.setSize({ 150, 150 });
	x_previewImage.setOrigin({ x_previewImage.getSize().x / 2 , x_previewImage.getSize().y / 2 });
	x_previewImage.setPosition({ WIDTH / 2, HEIGHT / 2 + ENTER_BOX_OFFSET });
	x_previewImage.setFillColor(sf::Color(xColor_r, xColor_g, xColor_b));

	o_previewImage.setTexture(data->assets.GetTexture(oPreviewImage));
	o_previewImage.setSize({ 150, 150 });
	o_previewImage.setOrigin({ o_previewImage.getSize().x / 2 , o_previewImage.getSize().y / 2 });
	o_previewImage.setPosition({ WIDTH / 2, HEIGHT / 2 + ENTER_BOX_OFFSET });
	o_previewImage.setFillColor(sf::Color(oColor_r, oColor_g, oColor_b));

	sf::Text acceptText("Accept", data->assets.GetFont(defaultFont), 40);
	acceptText.setOutlineColor(sf::Color::Black);
	acceptText.setOutlineThickness(2);
	acceptButton = Button({ 200, 75 }, acceptText, sf::Color::Black, { WIDTH / 2, HEIGHT - 150 }, 10);

	sf::sleep(sf::seconds(0.2));
}

void InitialSetupState1P::HandleInput()
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
		// if backspace has been released
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				Backspace = false;
			}
		}
		// clicked
		if (data->input.isButtonClicked(acceptButton.GetShape(), sf::Mouse::Left, data->window) && p1String.length() <= 8)
		{
			acceptButton.Clicked();
			sf::sleep(sf::seconds(1));
			data->machine.RemoveState();
			p1String = p1Text.getString();
			data->machine.AddState(stateReference(new GameState1P(data, p1String)), true);
		}
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			CheckHovered();
		}
	}
}

void InitialSetupState1P::Update()
{
	DrawBlackLine();
}

void InitialSetupState1P::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.draw(initialSetupShadow);
	data->window.draw(initialSetup);
	data->window.draw(enterTextP1);
	data->window.draw(p1Box);
	data->window.draw(p1Text);

	if (p1String.length() > 8)
	{
		data->window.draw(messageP1);
	}

	if (drawBlackLine)
	{
		data->window.draw(blackLine);
	}

	if (playerType == xPlayer)
	{
		data->window.draw(x_previewImage);
	}
	else
	{
		data->window.draw(o_previewImage);
	}

	acceptButton.DrawButton(data->window);

	data->window.display();
}

void InitialSetupState1P::CheckBoxClicked()
{
	checkBlackLineTimer = true;
	// p1Box
	if ((data->input.isButtonClicked(p1Box, sf::Mouse::Left, data->window)))
	{
		if (textBoxType != player)
		{
			textBoxType = player;
			blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);

			if (p1Input.getSize() <= 0)
			{
				blackLine.setPosition(WIDTH / 2 - 2, HEIGHT / 2 - ENTER_BOX_OFFSET);
			}
		}
	}
	// none
	else
	{
		textBoxType = nothing;
		checkBlackLineTimer = false;
		drawBlackLine = false;

		if (p1Input.getSize() <= 0)
		{
			p1Text.setString("Player");
			p1Text.setFillColor(sf::Color({ 120, 120, 120 }));
			p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
		}
	}
}

void InitialSetupState1P::CheckHovered()
{
	if (data->input.isButtonHovered(acceptButton.GetShape(), data->window) && p1String.length() > 8)
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
		if (acceptButton.GetShape().getPosition().y < HEIGHT - ACCEPT_OFFSET + 50)
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
