#include "Computer.h"

Computer::Computer()
{
}

Computer::Computer(bool PlayerPlaysX) : PlayerPlaysX(PlayerPlaysX)
{
}

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

bool Computer::CheckIfComputerCanWin(std::vector<BoardSquare>& boardSquares)
{
	boardTypes computerBoardType;
	if (PlayerPlaysX)
	{
		computerBoardType = o;
	}
	else
	{
		computerBoardType = x;
	}

	for (int i = 0; i < 3; i++)
	{
		// horizontally
		int counter = 0;
		bool canWin = true;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i * 3 + j].GetBoardType() == computerBoardType)
			{
				counter++;
			}
			else if (boardSquares[i * 3 + j].GetBoardType() != empty)
			{
				canWin = false;
				break;
			}
		}
		if (counter == 2 && canWin)
		{
			for (int j = 0; j < 3; j++)
			{
				if (boardSquares[i * 3 + j].GetBoardType() == empty)
				{
					SetComputerOption(i * 3 + j);

					return true;
				}
			}
		}

		// vertically
		counter = 0;
		canWin = true;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i + j * 3].GetBoardType() == computerBoardType)
			{
				counter++;
			}
			else if (boardSquares[i + j * 3].GetBoardType() != empty)
			{
				canWin = false;
				break;
			}
		}
		if (counter == 2 && canWin)
		{
			for (int j = 0; j < 3; j++)
			{
				if (boardSquares[i + j * 3].GetBoardType() == empty)
				{
					SetComputerOption(i + j * 3);

					return true;
				}
			}
		}
	}

	// slant
	if (boardSquares[0].GetBoardType() == computerBoardType && boardSquares[4].GetBoardType() == computerBoardType && boardSquares[8].GetBoardType() == empty)
	{
		SetComputerOption(8);

		return true;
	}
	else if (boardSquares[0].GetBoardType() == computerBoardType && boardSquares[4].GetBoardType() == empty && boardSquares[8].GetBoardType() == computerBoardType)
	{
		SetComputerOption(4);

		return true;
	}
	else if (boardSquares[0].GetBoardType() == empty && boardSquares[4].GetBoardType() == computerBoardType && boardSquares[8].GetBoardType() == computerBoardType)
	{
		SetComputerOption(0);

		return true;
	}

	if (boardSquares[2].GetBoardType() == computerBoardType && boardSquares[4].GetBoardType() == computerBoardType && boardSquares[6].GetBoardType() == empty)
	{
		SetComputerOption(6);

		return true;
	}
	else if (boardSquares[2].GetBoardType() == computerBoardType && boardSquares[4].GetBoardType() == empty && boardSquares[6].GetBoardType() == computerBoardType)
	{
		SetComputerOption(4);

		return true;
	}
	else if (boardSquares[2].GetBoardType() == empty && boardSquares[4].GetBoardType() == computerBoardType && boardSquares[6].GetBoardType() == computerBoardType)
	{
		SetComputerOption(2);

		return true;
	}

	return false;
}

bool Computer::CheckIfPlayerCanWin(std::vector<BoardSquare>& boardSquares)
{
	boardTypes playerBoardType;
	if (PlayerPlaysX)
	{
		playerBoardType = x;
	}
	else
	{
		playerBoardType = o;
	}

	for (int i = 0; i < 3; i++)
	{
		// horizontally
		bool isSafe = false;
		int counter = 0;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i * 3 + j].GetBoardType() == playerBoardType)
			{
				counter++;
			}
			else if (boardSquares[i * 3 + j].GetBoardType() != empty)
			{
				isSafe = true;
				break;
			}
		}
		if (counter == 2 && !isSafe)
		{
			for (int j = 0; j < 3; j++)
			{
				if (boardSquares[i * 3 + j].GetBoardType() == empty)
				{
					SetComputerOption(i * 3 + j);

					return true;
				}
			}
		}

		// vertically
		isSafe = false;
		counter = 0;
		for (int j = 0; j < 3; j++)
		{
			if (boardSquares[i + j * 3].GetBoardType() == playerBoardType)
			{
				counter++;
			}
			else if (boardSquares[i + j * 3].GetBoardType() != empty)
			{
				isSafe = true;
				break;
			}
		}
		if (counter == 2 && !isSafe)
		{
			for (int j = 0; j < 3; j++)
			{
				if (boardSquares[i + j * 3].GetBoardType() == empty)
				{
					SetComputerOption(i + j * 3);

					return true;
				}
			}
		}
	}

	// slant
	if (boardSquares[0].GetBoardType() == playerBoardType && boardSquares[4].GetBoardType() == playerBoardType && boardSquares[8].GetBoardType() == empty)
	{
		SetComputerOption(8);

		return true;
	}
	else if (boardSquares[0].GetBoardType() == playerBoardType && boardSquares[4].GetBoardType() == empty && boardSquares[8].GetBoardType() == playerBoardType)
	{
		SetComputerOption(4);

		return true;
	}
	else if (boardSquares[0].GetBoardType() == empty && boardSquares[4].GetBoardType() == playerBoardType && boardSquares[8].GetBoardType() == playerBoardType)
	{
		SetComputerOption(0);

		return true;
	}

	if (boardSquares[2].GetBoardType() == playerBoardType && boardSquares[4].GetBoardType() == playerBoardType && boardSquares[6].GetBoardType() == empty)
	{
		SetComputerOption(6);

		return true;
	}
	else if (boardSquares[2].GetBoardType() == playerBoardType && boardSquares[4].GetBoardType() == empty && boardSquares[6].GetBoardType() == playerBoardType)
	{
		SetComputerOption(4);

		return true;
	}
	else if (boardSquares[2].GetBoardType() == empty && boardSquares[4].GetBoardType() == playerBoardType && boardSquares[6].GetBoardType() == playerBoardType)
	{
		SetComputerOption(2);

		return true;
	}

	return false;
}

void Computer::SelectSquare(std::vector<BoardSquare>& boardSquares)
{
	if (CheckIfBoardIsEmpty(boardSquares))
	{
		return;
	}
	else if (CheckIfComputerCanWin(boardSquares))
	{
		return;
	}
	else if (CheckIfPlayerCanWin(boardSquares))
	{
		return;
	}
	else
	{
		std::vector<int> possibleMovements;
		for (int i = 0; i < boardSquares.size(); i++)
		{
			if (boardSquares[i].GetBoardType() == empty)
			{
				possibleMovements.emplace_back(i);
			}
		}

		int index = rand() % possibleMovements.size();
		SetComputerOption(possibleMovements[index]);
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
