#pragma once
#include "Visuals.h"
#include "GD.h"

class GL// Game Logic
{
public:
	GL(GLFWwindow* win, int wid, int hei);
	
	GD		d;	// data
	Visuals	v;	// visuals representation of data

	// main functions: 
	void initveryThing();
	void drawEveryThing(SpriteRenderer* renderer);
	void updateGameLogic(GLFWwindow* window);

	// clicking, dragging, placing squares
	void dragPiece(GLFWwindow* window);
	void dragPieceRelease(GLFWwindow* window);
	void placePieceOnNewSquare(GLFWwindow* window, int& iterator);
	void clickPlaceSquare(GLFWwindow* window);

	// animation
	void animatePiece(GLFWwindow* window);
	void updateRedSquares(GLFWwindow* window);

	// inputs
	glm::vec2 getMousePos(GLFWwindow* window);
	void mouseCallBack(GLFWwindow* window);

	// game logic
	bool areTouching(GLFWwindow* window, GameObject* object);	//square contains cursor
	glm::ivec2 getSquarePos(GLFWwindow* window);
	void createRedSuqare(GLFWwindow* window);
	// game logic
	
	void saveDirectionVector(glm::ivec2 oP, glm::ivec2 nP);
	bool PieceAnimation = false;
	int animatedPiece;
	glm::vec2 PieceMoveSpeed;
	glm::ivec2 newPos;
	int animCounter = 0;
	int animFPS = 25;
};

