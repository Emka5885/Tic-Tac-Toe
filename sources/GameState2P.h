#include "GameState.h"
#include "State.h"

class GameState2P :public State, GameState
{
private:
	GameDataReference data;

public:
	GameState2P(GameDataReference data, std::string& p1, std::string& p2);

	void Init();
	void HandleInput();
	void Update();
	void Draw();
};