#include "InitialSetupState.h"

void InitialSetupState::Create(GameDataReference& data)
{
	initialSetup.setString("Initial Setup");
	initialSetup.setCharacterSize(100);
	initialSetup.setFillColor(sf::Color::White);
	initialSetup.setOutlineColor(sf::Color::Black);
	initialSetup.setOutlineThickness(3);
	initialSetup.setFont(data->assets.GetFont(defaultFont));
	initialSetup.setOrigin(initialSetup.getGlobalBounds().width / 2, initialSetup.getGlobalBounds().height / 2);
	initialSetup.setPosition({ WIDTH / 2, 100 });
	initialSetupShadow = initialSetup;
	initialSetupShadow.setFillColor(sf::Color::Black);
	initialSetupShadow.setPosition({ WIDTH / 2 + 6, 105 });

	enterTextP1.setOutlineColor(sf::Color::Black);
	enterTextP1.setOutlineThickness(2);
	enterTextP1.setCharacterSize(25);
	enterTextP1.setString("Enter new player nickname:");
	enterTextP1.setFont(data->assets.GetFont(defaultFont));
	enterTextP1.setOrigin(enterTextP1.getGlobalBounds().width / 2, enterTextP1.getGlobalBounds().height / 2);

	p1Box.setOutlineColor(sf::Color::Black);
	p1Box.setOutlineThickness(4);
	p1Box.setSize({ TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y });
	p1Box.setOrigin(TEXT_BOX_SIZE_X / 2, TEXT_BOX_SIZE_Y / 2);

	blackLine.setSize({ 3, 50 });
	blackLine.setFillColor(sf::Color::Black);
	blackLine.setOrigin(blackLine.getSize().x / 2, blackLine.getSize().y / 2);

	messageP1.setString("maximum character length is 8");
	messageP1.setCharacterSize(15);
	messageP1.setFillColor(sf::Color::Red);
	messageP1.setOutlineColor(sf::Color::Black);
	messageP1.setOutlineThickness(1);
	messageP1.setFont(data->assets.GetFont(defaultFont));
	messageP1.setOrigin(messageP1.getGlobalBounds().width / 2, messageP1.getGlobalBounds().height / 2);

	x_previewImage.setTexture(data->assets.GetTexture(xPreviewImage));
	x_previewImage.setSize({ 150, 150 });
	x_previewImage.setOrigin({ x_previewImage.getSize().x / 2 , x_previewImage.getSize().y / 2 });
	x_previewImage.setFillColor(sf::Color(xColor_r, xColor_g, xColor_b));

	o_previewImage.setTexture(data->assets.GetTexture(oPreviewImage));
	o_previewImage.setSize({ 150, 150 });
	o_previewImage.setOrigin({ o_previewImage.getSize().x / 2 , o_previewImage.getSize().y / 2 });
	o_previewImage.setFillColor(sf::Color(oColor_r, oColor_g, oColor_b));

	sf::Text acceptText("Accept", data->assets.GetFont(defaultFont), 40);
	acceptText.setOutlineColor(sf::Color::Black);
	acceptText.setOutlineThickness(2);
	acceptButton = Button({ 200, 75 }, acceptText, sf::Color::Black, { WIDTH / 2, HEIGHT - 150 }, 10);
}

void InitialSetupState::ChangeP1Text()
{
	p1Text.setFillColor(sf::Color::Black);
	p1Text.setString(p1Input);
	p1Text.setOrigin(p1Text.getGlobalBounds().width / 2, p1Text.getGlobalBounds().height / 2);
	blackLine.setPosition(p1Text.getPosition().x + p1Text.getGlobalBounds().width / 2 + 4, HEIGHT / 2 - ENTER_BOX_OFFSET);
}

void InitialSetupState::DrawBlackLine()
{
	if (blackLineTimer.getElapsedTime().asSeconds() >= 0.5 && checkBlackLineTimer)
	{
		drawBlackLine = !drawBlackLine;
		blackLineTimer.restart();
	}
}

void InitialSetupState::CheckAcceptButtonHovered(GameDataReference& data)
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
