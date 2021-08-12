#include "Move.h"

Move::Move()
{
}

void Move::rook(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);
	// breaks loop out of this function
	bool breakLoop = false;

	// horizontal moves
	// left
	for (int i = pos.x - 1; i >= 0; i--)
		if (!breakLoop)
			checkCollision(squares, type, layout[pos.y][i], color, glm::ivec2(i, pos.y), breakLoop);
	// right
	breakLoop = false;
	for (int i = pos.x + 1; i <= 7; i++)
		if (!breakLoop)
			checkCollision(squares, type, layout[pos.y][i], color, glm::ivec2(i, pos.y), breakLoop);

	// vertical moves
	// up
	breakLoop = false;
	for (int i = pos.y - 1; i >= 0; i--)
		if (!breakLoop)
			checkCollision(squares, type, layout[i][pos.x], color, glm::ivec2(pos.x, i), breakLoop);
	// down
	breakLoop = false;
	for (int i = pos.y + 1; i <= 7; i++)
		if (!breakLoop)
			checkCollision(squares, type, layout[i][pos.x], color, glm::ivec2(pos.x, i), breakLoop);
}

void Move::bishop(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);
	// breaks loop out of this function
	bool breakLoop = false;

	// left-up
	glm::ivec2 temp(pos);
	for (int i = 0; i < std::min(pos.x, pos.y); i++)
		if (!breakLoop)
		{
			--temp.x; --temp.y;
			checkCollision(squares, type, layout[temp.y][temp.x], color, temp, breakLoop);
		}
	// right-up
	temp = pos; breakLoop = false;
	for (int i = 0; i < std::min(7 - pos.x, pos.y); i++)
		if (!breakLoop)
		{
			++temp.x; --temp.y;
			checkCollision(squares, type, layout[temp.y][temp.x], color, temp, breakLoop);
		}
	// left-down
	temp = pos; breakLoop = false;
	for (int i = 0; i < std::min(pos.x, 7 - pos.y); i++)
		if (!breakLoop)
		{
			--temp.x; ++temp.y;
			checkCollision(squares, type, layout[temp.y][temp.x], color, temp, breakLoop);
		}
	// right-down
	temp = pos; breakLoop = false;
	for (int i = 0; i < std::min(7 - pos.x, 7 - pos.y); i++)
		if (!breakLoop)
		{
			++temp.x; ++temp.y;
			checkCollision(squares, type, layout[temp.y][temp.x], color, temp, breakLoop);
		}
}

void Move::downPawn(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);

	// regular moves
	if ((pos.y == 6) && !layout[pos.y - 1][pos.x] && !layout[pos.y - 2][pos.x]) //7th rank allows to move 2 squares forward
	{
		for (int i = 1; i <= 2; i++)
		{
			squares.push_back(glm::ivec2(pos.x, pos.y - i));
			type.push_back(0);
		}
	}
	else if ((pos.y <= 6 && pos.y > 0) && !layout[pos.y - 1][pos.x]) // 1 square forward
	{
		squares.push_back(glm::ivec2(pos.x, pos.y - 1));
		type.push_back(0);
	}

	// captures
	if (layout[pos.y - 1][pos.x - 1] * color < 0)
	{
		squares.push_back(glm::ivec2(pos.x - 1, pos.y - 1));
		type.push_back(1);
	}
	if (layout[pos.y - 1][pos.x + 1] * color < 0)
	{
		squares.push_back(glm::ivec2(pos.x + 1, pos.y - 1));
		type.push_back(1);
	}


}

void Move::upPawn(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);

	if (pos.y == 1 && !layout[pos.y + 1][pos.x] && !layout[pos.y + 2][pos.x]) //7th rank allows to move 2 squares forward
	{
		for (int i = 1; i <= 2; i++)
		{
			squares.push_back(glm::ivec2(pos.x, pos.y + i));
			type.push_back(0);
		}
	}
	else if ((pos.y < 7 && pos.y >= 1) && !layout[pos.y + 1][pos.x]) // 1 square forward
	{
		squares.push_back(glm::ivec2(pos.x, pos.y + 1));
		type.push_back(0);
	}

	// captures
	if (layout[pos.y + 1][pos.x - 1] * color < 0)
	{
		squares.push_back(glm::ivec2(pos.x - 1, pos.y + 1));
		type.push_back(1);
	}
	if (layout[pos.y + 1][pos.x + 1] * color < 0)
	{
		squares.push_back(glm::ivec2(pos.x + 1, pos.y + 1));
		type.push_back(1);
	}
}

void Move::queen(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	rook(squares, type, pos, layout);
	bishop(squares, type, pos, layout);
}

void Move::knight(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);
	// breaks loop out of this function
	bool breakLoop = false;

	// possible knight moves
	int row[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	int col[8] = { -1, 1, 1, -1, 2, -2, 2, -2 };

	for (int i = 0; i < 8; i++)
		if (isInBoardRange(pos, row[i], col[i]))
		{
			if (layout[pos.y + row[i]][pos.x + col[i]] == 0)// is empty square
			{
				squares.push_back(glm::vec2(pos.x + col[i], pos.y + row[i]));
				type.push_back(0);
			}
			else if (layout[pos.y + row[i]][pos.x + col[i]] * color <= 0) // is opponent square
			{
				squares.push_back(glm::vec2(pos.x + col[i], pos.y + row[i]));
				type.push_back(1);
			}
		}
}

void Move::king(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8])
{
	// get piece color (white: 1, black: -1)
	int color = getPieceColor(layout[pos.y][pos.x]);
	// breaks loop out of this function
	bool breakLoop = false;

	int row[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int col[8] = { -1,-1,-1,  0, 0,  1, 1, 1 };

	for (int i = 0; i < 8; i++)
		if (isInBoardRange(pos, row[i], col[i]))
		{
			if (layout[pos.y + row[i]][pos.x + col[i]] == 0)// is empty square
			{
				squares.push_back(glm::vec2(pos.x + col[i], pos.y + row[i]));
				type.push_back(0);
			}
			else if (layout[pos.y + row[i]][pos.x + col[i]] * color <= 0) // is opponent square
			{
				squares.push_back(glm::vec2(pos.x + col[i], pos.y + row[i]));
				type.push_back(1);
			}
		}
			

}

bool Move::isInBoardRange(glm::ivec2& pos, int row, int col)
{
	return (
		(pos.x + col >= 0 && pos.x + col <= 7)    //col=vieta rindâ
		&& (pos.y + row >= 0 && pos.y + row <= 7) //row=vieta kolonna
		);
}

int Move::getPieceColor(int square)
{
	return (square > 0) ? 1 : -1;
}

void Move::checkCollision(std::vector<glm::ivec2>& squares, std::vector<bool>& type, int& pieceRef,
	int& color, glm::ivec2 newPos, bool& breakLoop)
{
	breakLoop = false;
	if (pieceRef == 0)
	{
		squares.push_back(glm::vec2(newPos.x, newPos.y));
		type.push_back(0);
	}
	else if (pieceRef * color < 0)
	{
		squares.push_back(glm::vec2(newPos.x, newPos.y));
		type.push_back(1);
		breakLoop = true;
	}
	else breakLoop = true;
}


