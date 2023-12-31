#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "BoardSquare.h"

class Computer
{
private:
	computerOptions computerOption = defaultOption;
	bool PlayerPlaysX = false;

protected:
	bool CheckIfBoardIsEmpty(std::vector<BoardSquare>& boardSquares);

	bool CheckIfComputerCanWin(std::vector<BoardSquare>& boardSquares);

	bool CheckIfPlayerCanWin(std::vector<BoardSquare>& boardSquares);

	void SetComputerOption(int number);

public:
	Computer();
	Computer(bool PlayerPlaysX);

	void SelectSquare(std::vector<BoardSquare>& boardSquares);
	computerOptions& GetComputerOption();
};