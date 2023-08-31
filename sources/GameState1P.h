#include "GameState.h"
#include "State.h"
#include "Computer.h"

class GameState1P :public State, GameState
{
private:
	GameDataReference data;
	bool FirstPlayerPlaysX;
	bool start = true;
	Computer computer;
	sf::Clock startClock;
	sf::Clock waitClock;

public:
	GameState1P(GameDataReference data, std::string& player, bool FirstPlayerPlaysX);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

	void SetComputerSelection();
};