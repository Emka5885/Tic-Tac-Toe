#include "OptionsState.h"
#include "MainMenuState.h"
#include "Definitions.h"

OptionsState::OptionsState(GameDataReference data) : data(data)
{
}

void OptionsState::Init()
{
	options = sf::Text("Options", data->assets.GetFont(defaultFont), 100);
	options.setOrigin(options.getGlobalBounds().width / 2, options.getGlobalBounds().height / 2);
	options.setPosition({ WIDTH / 2, 100 });
	options.setFillColor(sf::Color::White);
	options.setOutlineColor(sf::Color::Black);
	options.setOutlineThickness(3);
	optionsShadow = options;
	optionsShadow.setFillColor(sf::Color::Black);
	optionsShadow.setPosition({ WIDTH / 2 + 6, 105 });

	sf::Text buttonsText("Back to Main Menu", data->assets.GetFont(defaultFont), 50);
	buttonsText.setFillColor(sf::Color(250, 250, 250));
	buttonsText.setOutlineColor(sf::Color::Black);
	buttonsText.setOutlineThickness(2);
	sf::Vector2f buttonsSize(WIDTH - 200, 85);

	backButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, HEIGHT - 100 - buttonsSize.y / 2 }, 10);
}

void OptionsState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
		// check menu type
		if (event.type == sf::Event::Closed)
		{
			sf::sleep(sf::seconds(1));
			data->window.close();
		}
		// clicked
		if (data->input.isButtonClicked(backButton.GetShape(), sf::Mouse::Left, data->window))
		{
			backButton.Clicked();
			data->machine.RemoveState();
			data->machine.AddState(stateReference(new MainMenuState(data)), true);
		}
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			if (data->input.isButtonHovered(backButton.GetShape(), data->window))
			{
				backButton.ChangeHover(true);
			}
			else
			{
				backButton.ChangeHover(false);
			}
		}
	}
}

void OptionsState::Update()
{
}

void OptionsState::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.draw(optionsShadow);
	data->window.draw(options);
	backButton.DrawButton(data->window);

	data->window.display();
}
