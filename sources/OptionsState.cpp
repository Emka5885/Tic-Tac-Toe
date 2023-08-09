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
	grayShape.setFillColor(sf::Color(sf::Color(105, 105, 105)));
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
		if (event.type == sf::Event::MouseMoved)
		{
			// hovered
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

	backButton.DrawButton(data->window);

	data->window.display();
}
