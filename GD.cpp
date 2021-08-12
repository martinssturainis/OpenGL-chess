#include "GD.h"

GD::GD(unsigned int scrWidth, unsigned int scrHeight)
	: board{
	-1, -2, -3, -5, -4, -3, -2, -1,
	-6, -6, -6, -6, -6, -6, -6, -6,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 6,  6,  6,  6,  6,  6,  6,  6,
	 1,  2,  3,  5,  4,  3,  2,  1 },
	tileSize(new float((float)scrWidth / 8)), selected(new int(-1)),
	lgType(new std::vector<bool>), legalSquares(new std::vector<glm::ivec2>)
{
}

void GD::printBoard()
{
	system("CLS");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] >= 0) std::cout << "  ";
			else std::cout << " ";
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}

glm::vec2 GD::getSquareLayoutPos(glm::vec2& pos)
{
	return glm::vec2(
		(int)(pos.x / *tileSize),
		(int)(pos.y / *tileSize));
}