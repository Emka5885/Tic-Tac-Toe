#include "InitialSetupState.h"
#include "State.h"

enum textBoxesTypes { none, player1, player2 };

class InitialSetupState2P :public State, InitialSetupState
{
private:
	GameDataReference data;

	sf::RectangleShape p2Box;

	std::string p2String;
	sf::String p2Input;
	sf::Text p2Text;
	sf::Text enterTextP2;
	sf::Text messageP2;

	textBoxesTypes textBoxType = player1;

public:
	InitialSetupState2P(GameDataReference data);

	void Init();
	void HandleInput();
	void Update();
	void Draw();

	void ChangeP2Text();

	void CheckBoxClicked();
};