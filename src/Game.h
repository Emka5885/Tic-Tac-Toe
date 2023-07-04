#pragma once
#include <memory>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
	sf::Text name;
};

typedef std::shared_ptr<GameData> GameDataReference;

class Game
{
public:
	Game(std::string title);

	void Init();
	void Run();

private:
	std::fstream file;
	sf::Image image;

	std::string title;

	const float dt = 1.0f / 60.0f;
	sf::Clock clock;

	GameDataReference data = std::make_shared<GameData>();
};