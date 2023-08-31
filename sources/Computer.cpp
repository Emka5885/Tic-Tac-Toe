#include "Computer.h"

bool Computer::CheckIfBoardIsEmpty(std::vector<BoardSquare>& boardSquares)
{
	for (int i = 0; i < boardSquares.size(); i++)
	{
		if (boardSquares[i].GetBoardType() != empty)
		{
			return false;
		}
	}

	int random = rand() % 9;
	SetComputerOption(random);

	return true;
}

void Computer::SelectSquare(std::vector<BoardSquare>& boardSquares)
{
	if (!CheckIfBoardIsEmpty(boardSquares))
	{
		for (int i = 0; i < boardSquares.size(); i++)
		{
			if (boardSquares[i].GetBoardType() == empty)
			{
				SetComputerOption(i);
			}
		}
	}
}

void Computer::SetComputerOption(int number)
{
	switch (number)
	{
	case 0:
		computerOption = firstSquare;
		break;
	case 1:
		computerOption = secondSquare;
		break;
	case 2:
		computerOption = thirdSquare;
		break;
	case 3:
		computerOption = fourthSquare;
		break;
	case 4:
		computerOption = fifthSquare;
		break;
	case 5:
		computerOption = sixthSquare;
		break;
	case 6:
		computerOption = seventhSquare;
		break;
	case 7:
		computerOption = eighthSquare;
		break;
	case 8:
		computerOption = ninthSquare;
		break;
	}
}

computerOptions& Computer::GetComputerOption()
{
	return computerOption;
}
