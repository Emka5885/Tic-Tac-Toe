#include "MainMenuState.h"
#include "OptionsState.h"
#include "InitialSetupState1P.h"
#include "InitialSetupState2P.h"
#include "Definitions.h"

MainMenuState::MainMenuState(GameDataReference& data) : data(data)
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

	std::ifstream file;
	file.open("options.dat", std::ios_base::out | std::ios_base::binary);
	if (file.is_open())
	{
		std::vector<std::pair<optionsTypes, int>> optionsFromFile(NUMBER_OF_OPTIONS);
		for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
		{
			file.read((char*)&optionsFromFile[i], sizeof(std::pair<optionsTypes, int>));

			if (optionsFromFile[i].first == mode)
			{
				if (optionsFromFile[i].second == 2)
				{
					mType = twoPlayerType;
				}
				break;
			}
		}

		file.close();
	}

	sf::sleep(sf::seconds(0.2));
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		// check menu type
		if (event.type == sf::Event::Closed || type == quitt)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		else if (type == play)
		{
			data->machine.RemoveState();
			if (mType == onePlayerType)
			{
				data->machine.AddState(stateReference(new InitialSetupState1P(data)), true);
			}
			else
			{
				data->machine.AddState(stateReference(new InitialSetupState2P(data)), true);
			}
		}
		else if (type == options)
		{
			data->machine.RemoveState();
			data->machine.AddState(stateReference(new OptionsState(data)), true);
		}
		// clicked
		if (data->input.isButtonClicked(quittButton.GetShape(), sf::Mouse::Left, data->window))
		{
			quittButton.Clicked();
			type = quitt;
			data->gameAudio.PlaySound();
		}
		else if (data->input.isButtonClicked(playButton.GetShape(), sf::Mouse::Left, data->window))
		{
			playButton.Clicked();
			type = play;
			data->gameAudio.PlaySound();
		}
		else if (data->input.isButtonClicked(optionsButton.GetShape(), sf::Mouse::Left, data->window))
		{
			optionsButton.Clicked();
			type = options;
			data->gameAudio.PlaySound();
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
