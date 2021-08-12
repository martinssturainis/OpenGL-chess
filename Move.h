#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"

class Move
{
public:
	Move();
	// pieces
	static void rook(std::vector<glm::ivec2>&squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void bishop(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void downPawn(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void upPawn(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void queen(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void knight(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);
	static void king(std::vector<glm::ivec2>& squares, std::vector<bool>& type, glm::ivec2 pos, int layout[][8]);

	// piece, if moved, stays on the board
	static bool isInBoardRange(glm::ivec2& pos, int row, int col);
	static int getPieceColor(int square);
	static void checkCollision(std::vector<glm::ivec2>& squares, std::vector<bool>& type, int& pieceRef,
		int& color, glm::ivec2 newPos, bool& breakLoop);
};

