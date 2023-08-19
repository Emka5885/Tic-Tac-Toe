#include "InitialSetupState.h"
#include "State.h"
#include "Game.h"

enum textBoxTypes { nothing, player};

class InitialSetupState1P :public State, InitialSetupState
{
private:
	GameDataReference data;

	textBoxTypes textBoxType = nothing;

public:
	InitialSetupState1P(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

	void CheckBoxClicked();
	void CheckHovered();
};