#include "GameState.h"
#include "State.h"

class GameState1P :public State, GameState
{
private:
	GameDataReference data;

public:
	GameState1P(GameDataReference data, std::string& player);

	void Init();
	void HandleInput();
	void Update();
	void Draw();
};