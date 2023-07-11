#include "GameState.h"

GameState::GameState(GameDataReference data) : data(data)
{
}

void GameState::Init()
{
}

void GameState::HandleInput()
{
}

void GameState::Update()
{
}

void GameState::Draw()
{
	data->window.clear(sf::Color(165, 165, 165));

	data->window.display();
}
