#include "Game.h"
#include "MainMenuState.h"

Game::Game()
{
}

void Game::Init()
{
	srand(time(NULL));
	data->window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close | sf::Style::Titlebar);

	iconImage = data->assets.GetTexture(icon)->copyToImage();
	data->window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

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