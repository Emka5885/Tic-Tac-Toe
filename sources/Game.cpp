#include "Game.h"
#include "MainMenuState.h"

Game::Game(std::string title) : title(title)
{
}

void Game::Init()
{
	srand(time(NULL));
	data->window.create(sf::VideoMode(WIDTH, HEIGHT), title, sf::Style::Close | sf::Style::Titlebar);

	if (!image.loadFromFile("resources/Icon.png"))
	{
		std::cout << "Error - icon.\n";
	}
	data->window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	data->machine.AddState(stateReference(new MainMenuState(data)), true);
}


void Game::Run()
{
	float newTime, frameTime;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->data->window.isOpen())
	{
		this->data->machine.ProcessStateChanges();

		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->data->machine.GetActiveState()->HandleInput();

			if (!this->data->window.isOpen())
			{
				return;
			}

			this->data->machine.GetActiveState()->Update();

			accumulator -= dt;
		}
		this->data->machine.GetActiveState()->Draw();
	}
}