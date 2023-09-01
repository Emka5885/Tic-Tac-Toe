#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "BoardSquare.h"

class Computer
{
private:
	computerOptions computerOption;
	bool PlayerPlaysX;

protected:
	bool CheckIfBoardIsEmpty(std::vector<BoardSquare>& boardSquares);

	bool CheckIfComputerCanWin(std::vector<BoardSquare>& boardSquares);

	bool CheckIfPlayerCanWin(std::vector<BoardSquare>& boardSquares);

	void SetComputerOption(int number);

public:
	Computer(bool PlayerPlaysX = true);

	void SelectSquare(std::vector<BoardSquare>& boardSquares);
	computerOptions& GetComputerOption();
};