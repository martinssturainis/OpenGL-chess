#pragma once // game data. main data for AI
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"

class GD
{
public:
	GD(unsigned int scrWidth, unsigned int scrHeight);
	void printBoard();
	
	// real data
	int board[8][8];
	float* tileSize;

	std::vector<glm::ivec2>* legalSquares;		
	std::vector<bool>* lgType;

	glm::ivec2 originalSquarePos;	
	GameObject* avaibleMove;				
	glm::vec2 getSquareLayoutPos(glm::vec2& pos);

	int* selected;		//selected piece number. Used for finding piece in loop
	int selectedSaved = -1;	//selected piece number. Used for finding piece in loop
	int avaiblePieces = 0;
	bool whiteToMove = true;
	bool rmbHolding = false;	   // places/deletes red squares
	bool movingPiece = false;   // starts/ends piece dragging
};

