#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "BoardSquare.h"

class Computer
{
private:
	computerOptions computerOption;

protected:
	bool CheckIfBoardIsEmpty(std::vector<BoardSquare>& boardSquares);
	void SetComputerOption(int number);

public:
	Computer() {}

	void SelectSquare(std::vector<BoardSquare>& boardSquares);
	computerOptions& GetComputerOption();
};