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

	sf::Text grayShapeText("Mode", data->assets.GetFont(defaultFont), 45);
	grayShapeText.setFillColor(sf::Color(250, 250, 250));
	grayShapeText.setOutlineColor(sf::Color::Black);
	grayShapeText.setOutlineThickness(2);

	sf::RectangleShape grayShape({ WIDTH - 300, 70 });
	grayShape.setFillColor(sf::Color(105, 105, 105));
	grayShape.setOutlineColor(sf::Color::Black);
	grayShape.setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	grayShapeText.setPosition(175, 222);
	grayShape.setPosition(150, 215);
	grayRectangles.emplace_back(std::pair<sf::RectangleShape, sf::Text>());
	grayRectangles.back().first = grayShape;
	grayRectangles.back().second = grayShapeText;
	grayShapeText.setPosition(180, 225);
	textShadows.emplace_back(grayShapeText);

	grayShapeText.setString("Music");
	grayShapeText.setPosition(175, 317);
	grayShape.setPosition(150, 310);
	grayRectangles.emplace_back(std::pair<sf::RectangleShape, sf::Text>());
	grayRectangles.back().first = grayShape;
	grayRectangles.back().second = grayShapeText;
	grayShapeText.setPosition(180, 320);
	textShadows.emplace_back(grayShapeText);

	grayShape.setSize({ WIDTH - 300, 50 });
	grayShape.setPosition(150, 395);
	grayRectangles.emplace_back(std::pair<sf::RectangleShape, sf::Text>());
	grayRectangles.back().first = grayShape;

	coverMusic = grayShape;
	coverMusic.setFillColor(sf::Color(165, 165, 165));
	coverMusic.setSize({ WIDTH - 290, 60 });
	coverMusic.setPosition(145, 390);
	coverMusic.setOutlineThickness(0);
	coverSounds = coverMusic;
	coverSounds.setPosition(145, 545);

	grayShapeText.setString("Sounds");
	grayShapeText.setPosition(175, 472);
	grayShape.setSize({ WIDTH - 300, 70 });
	grayShape.setPosition(150, 465);
	grayRectangles.emplace_back(std::pair<sf::RectangleShape, sf::Text>());
	grayRectangles.back().first = grayShape;
	grayRectangles.back().second = grayShapeText;
	grayShapeText.setPosition(180, 475);
	textShadows.emplace_back(grayShapeText);

	grayShape.setSize({ WIDTH - 300, 50 });
	grayShape.setPosition(150, 550);
	grayRectangles.emplace_back(std::pair<sf::RectangleShape, sf::Text>());
	grayRectangles.back().first = grayShape;

	for (int i = 0; i < textShadows.size(); i++)
	{
		textShadows[i].setFillColor(sf::Color::Black);
	}

	sf::Text buttonsText("Back to Main Menu", data->assets.GetFont(defaultFont), 45);
	buttonsText.setFillColor(sf::Color(250, 250, 250));
	buttonsText.setOutlineColor(sf::Color::Black);
	buttonsText.setOutlineThickness(2);
	sf::Vector2f buttonsSize(WIDTH - 300, 75);

	backButton = Button(buttonsSize, buttonsText, sf::Color::Black, { WIDTH / 2, HEIGHT - 90 - buttonsSize.y / 2 }, 10);

	musicScrollBar = ScrollBar({ WIDTH / 2, 420 }, 50);
	soundsScrollBar = ScrollBar({ WIDTH / 2, 575 }, 50);

	buttonsText.setString("On");
	buttonsText.setOrigin(buttonsText.getGlobalBounds().width / 2, buttonsText.getGlobalBounds().height - buttonsText.getGlobalBounds().height / 5);
	musicOnSwitchButton = SwitchButton({ WIDTH / 2 + 60, 345 }, buttonsText, true);
	soundsOnSwitchButton = SwitchButton({ WIDTH / 2 + 60, 500 }, buttonsText, true);

	buttonsText.setString("Off");
	buttonsText.setOrigin(buttonsText.getGlobalBounds().width / 2, buttonsText.getGlobalBounds().height - buttonsText.getGlobalBounds().height / 3);
	musicOffSwitchButton = SwitchButton({ WIDTH / 2 + 165, 345 }, buttonsText);
	soundsOffSwitchButton = SwitchButton({ WIDTH / 2 + 165, 500 }, buttonsText);

	buttonsText.setString("1p");
	buttonsText.setOrigin(buttonsText.getGlobalBounds().width / 2, buttonsText.getGlobalBounds().height - buttonsText.getGlobalBounds().height / 3);
	onePSwitchButton = SwitchButton({ WIDTH / 2 + 60, 250 }, buttonsText);
	buttonsText.setString("2p");
	buttonsText.setOrigin(buttonsText.getGlobalBounds().width / 2, buttonsText.getGlobalBounds().height - buttonsText.getGlobalBounds().height / 3);
	twoPSwitchButton = SwitchButton({ WIDTH / 2 + 165, 250 }, buttonsText, true);
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
		// hovered
		if (event.type == sf::Event::MouseMoved)
		{
			ChangeButtonsHoverd();
		}
		// clicked
		CheckButtonsClicked();
	}

	musicScrollBar.Update(event, sf::Vector2f(data->input.GetMousePosition(data->window)));
	soundsScrollBar.Update(event, sf::Vector2f(data->input.GetMousePosition(data->window)));

}

void OptionsState::Update()
{
}

void OptionsState::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.draw(optionsShadow);
	data->window.draw(options);

	for (int i = 0; i < grayRectangles.size(); i++)
	{
		data->window.draw(grayRectangles[i].first);
	}

	musicScrollBar.Draw(data->window);
	soundsScrollBar.Draw(data->window);

	for (int i = 0; i < textShadows.size(); i++)
	{
		data->window.draw(textShadows[i]);
	}

	for (int i = 0; i < grayRectangles.size(); i++)
	{
		data->window.draw(grayRectangles[i].second);
	}

	musicOnSwitchButton.Draw(data->window);
	musicOffSwitchButton.Draw(data->window);
	soundsOnSwitchButton.Draw(data->window);
	soundsOffSwitchButton.Draw(data->window);
	onePSwitchButton.Draw(data->window);
	twoPSwitchButton.Draw(data->window);

	if (!musicOnSwitchButton.GetActive())
	{
		data->window.draw(coverMusic);
	}
	if (!soundsOnSwitchButton.GetActive())
	{
		data->window.draw(coverSounds);
	}

	backButton.DrawButton(data->window);

	data->window.display();
}

void OptionsState::ChangeButtonsHoverd()
{
	// back
	if (data->input.isButtonHovered(backButton.GetShape(), data->window))
	{
		backButton.ChangeHover(true);
	}
	else
	{
		backButton.ChangeHover(false);
	}

	// music
	if (!musicOnSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(musicOnSwitchButton.GetShape(), data->window))
		{
			musicOnSwitchButton.ChangeHover(true);
		}
		else
		{
			musicOnSwitchButton.ChangeHover(false);
		}
	}
	if (!musicOffSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(musicOffSwitchButton.GetShape(), data->window))
		{
			musicOffSwitchButton.ChangeHover(true);
		}
		else
		{
			musicOffSwitchButton.ChangeHover(false);
		}
	}

	// sounds
	if (!soundsOnSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(soundsOnSwitchButton.GetShape(), data->window))
		{
			soundsOnSwitchButton.ChangeHover(true);
		}
		else
		{
			soundsOnSwitchButton.ChangeHover(false);
		}
	}
	if (!soundsOffSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(soundsOffSwitchButton.GetShape(), data->window))
		{
			soundsOffSwitchButton.ChangeHover(true);
		}
		else
		{
			soundsOffSwitchButton.ChangeHover(false);
		}
	}

	// mode
	if (!onePSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(onePSwitchButton.GetShape(), data->window))
		{
			onePSwitchButton.ChangeHover(true);
		}
		else
		{
			onePSwitchButton.ChangeHover(false);
		}
	}
	if (!twoPSwitchButton.GetActive())
	{
		if (data->input.isButtonHovered(twoPSwitchButton.GetShape(), data->window))
		{
			twoPSwitchButton.ChangeHover(true);
		}
		else
		{
			twoPSwitchButton.ChangeHover(false);
		}
	}
}

void OptionsState::CheckButtonsClicked()
{
	// back
	if (data->input.isButtonClicked(backButton.GetShape(), sf::Mouse::Left, data->window))
	{
		backButton.Clicked();
		data->machine.RemoveState();
		data->machine.AddState(stateReference(new MainMenuState(data)), true);
	}
	// music
	else if (data->input.isButtonClicked(musicOnSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		musicOnSwitchButton.ChangeInActivity(true);
		musicOffSwitchButton.ChangeInActivity(false);
	}
	else if (data->input.isButtonClicked(musicOffSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		musicOnSwitchButton.ChangeInActivity(false);
		musicOffSwitchButton.ChangeInActivity(true);
	}
	// sounds
	else if (data->input.isButtonClicked(soundsOnSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		soundsOnSwitchButton.ChangeInActivity(true);
		soundsOffSwitchButton.ChangeInActivity(false);
	}
	else if (data->input.isButtonClicked(soundsOffSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		soundsOnSwitchButton.ChangeInActivity(false);
		soundsOffSwitchButton.ChangeInActivity(true);
	}
	// mode
	else if (data->input.isButtonClicked(onePSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		onePSwitchButton.ChangeInActivity(true);
		twoPSwitchButton.ChangeInActivity(false);
	}
	else if (data->input.isButtonClicked(twoPSwitchButton.GetShape(), sf::Mouse::Left, data->window))
	{
		onePSwitchButton.ChangeInActivity(false);
		twoPSwitchButton.ChangeInActivity(true);
	}
}
