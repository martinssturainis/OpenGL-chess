#pragma once

// Galvenâ funckionalitâte: vizualizçt GL - Game Logic faila datus
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "GD.h"
#include "Move.h"
#include <GLFW/glfw3.h>

class Visuals
{
public:
	// galvenâs funkcijas
	Visuals(float* tSize, int* slt, std::vector <bool>* lgType, std::vector<glm::ivec2>* lgS);
	std::vector<glm::ivec2>* legalSquares;
	std::vector<bool>* lgType;

	void initVisuals(int board[8][8]);
	void renderBoard(SpriteRenderer* renderer);

	// realtime updates
	void showAvaibleMoves(GLFWwindow* window, std::vector<glm::ivec2>& ls, std::vector<bool>& lgT, 
		glm::ivec2 sqPos, int board[8][8]);
	void createAvaibleMoveDots(std::vector<glm::ivec2>& ls, std::vector<bool>& lgT);
	void placeJellowSquare(GLFWwindow* window, glm::ivec2 position, int i);

	// mainîgie/objekti
	GameObject* boardSquare[8][8]; //chess board squares
	GameObject* object[32];		  //textured chess piece objects
	GameObject* yellowSquare[2];	  //selected piece starting square
	std::vector<GameObject*> redSquares;  //rmb red squares
	std::vector<GameObject*> legalSquareDots;	//legal squares
	GameObject* avaibleMove;	//legalsquaresdots object

private:
	// pointers from G
	float* tileSize; //tileSize copy
	int* selected;   //selected piece number copy
	void setPieces(int board[8][8]);
	void setAttributes();
	void setBoard();
};

