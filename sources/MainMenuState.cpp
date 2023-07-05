#include <iostream>
#include "MainMenuState.h"

MainMenuState::MainMenuState(GameDataReference data) : data(data)
{
}

void MainMenuState::Init()
{
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (data->window.pollEvent(event))
	{
	}
}

void MainMenuState::Update()
{
}

void MainMenuState::Draw()
{
	data->window.clear(sf::Color::White);

	data->window.display();
}
