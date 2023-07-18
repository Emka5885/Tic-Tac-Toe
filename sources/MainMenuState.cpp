#include "MainMenuState.h"
#include "InitialSetupState.h"
#include "Definitions.h"

MainMenuState::MainMenuState(GameDataReference data) : data(data)
{
}

void MainMenuState::Init()
{
	title = sf::Text(TITLE, data->assets.GetFont(defaultFont), 100);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition({ WIDTH / 2, 100 });
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(3);
	titleShadow = title;
	titleShadow.setFillColor(sf::Color::Black);
	titleShadow.setPosition({ WIDTH / 2 + 6, 105 });

	sf::Text buttonsText("Play", data->assets.GetFont(defaultFont), 50);
	buttonsText.setFillColor(sf::Color(250, 250, 250));
	buttonsText.setOutlineColor(sf::Color::Black);
	buttonsText.setOutlineThickness(2);
	sf::Vector2f buttonsSize(250, 100);

	playButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, title.getPosition().y + title.getGlobalBounds().height + 115 }, 10);

	buttonsText.setString("Options");
	optionsButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, playButton.GetShape().getPosition().y + 165 }, 10);

	buttonsText.setString("Quitt");
	quittButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, optionsButton.GetShape().getPosition().y + 165 }, 10);
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		// check menu type
		if (event.type == sf::Event::Closed || type == 3)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		else if (type == 1)
		{
			sf::sleep(sf::seconds(1));
			data->machine.RemoveState();
			data->machine.AddState(stateReference(new InitialSetupState(data)), true);
		}
		else if (type == 2)
		{
			sf::sleep(sf::seconds(1));

		}
		// clicked
		if (data->input.isButtonClicked(quittButton.GetShape(), sf::Mouse::Left, data->window))
		{
			quittButton.Clicked();
			type = quitt;
		}
		else if (data->input.isButtonClicked(playButton.GetShape(), sf::Mouse::Left, data->window))
		{
			playButton.Clicked();
			type = play;
		}
		else if (data->input.isButtonClicked(optionsButton.GetShape(), sf::Mouse::Left, data->window))
		{
			optionsButton.Clicked();
			type = options;
		}
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			if (data->input.isButtonHovered(playButton.GetShape(), data->window))
			{
				playButton.ChangeHover(true);
			}
			else
			{
				playButton.ChangeHover(false);
			}

			if (data->input.isButtonHovered(optionsButton.GetShape(), data->window))
			{
				optionsButton.ChangeHover(true);
			}
			else
			{
				optionsButton.ChangeHover(false);
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

void MainMenuState::Update()
{
}

void MainMenuState::Draw()
{
	data->window.clear(sf::Color(165,165,165));

	data->window.draw(titleShadow);
	data->window.draw(title);
	playButton.DrawButton(data->window);
	optionsButton.DrawButton(data->window);
	quittButton.DrawButton(data->window);

	data->window.display();
}
