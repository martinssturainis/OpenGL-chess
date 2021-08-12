#include "GL.h" //Game Logic

GL::GL(GLFWwindow* win, int wid, int hei)
	: d(wid, hei), v(d.tileSize, d.selected, d.lgType, d.legalSquares)
	//legalSquaresPtr
{
}

// main functions
void GL::initveryThing()
{
	v.initVisuals(d.board);
	
}

void GL::drawEveryThing(SpriteRenderer* renderer)
{
	v.renderBoard(renderer);
}

void GL::updateGameLogic(GLFWwindow* window)
{
	mouseCallBack(window);
	animatePiece(window);
}

// mouse handling fucntions

void GL::mouseCallBack(GLFWwindow* window)
{
	// place square in position after single click
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !d.movingPiece)
		clickPlaceSquare(window);

	// click and hold selected piece
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		dragPiece(window);

	// release and set new position for selected piece
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		dragPieceRelease(window);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && !d.rmbHolding)
	{
		updateRedSquares(window);
		d.rmbHolding = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE && d.rmbHolding)
		d.rmbHolding = false;
}

void GL::dragPiece(GLFWwindow* window)
{
	if (!PieceAnimation)
	{
		// move piece
		d.avaiblePieces = (d.whiteToMove) ? 16 : 0;
		if (*d.selected == -1)
			for (int i = d.avaiblePieces; i < d.avaiblePieces + 16; i++)
				// clicked on piece
				if (areTouching(window, v.object[i]) && !d.movingPiece)
				{
					*d.selected = i; d.selectedSaved = *d.selected; d.movingPiece = true;
					
					// show avaible moves
					v.showAvaibleMoves(window, *d.legalSquares, *d.lgType,getSquarePos(window),d.board);
					// save selected square original position
					d.originalSquarePos = getSquarePos(window);
					// place jellow tile and show avaible moves
					v.placeJellowSquare(window, getSquarePos(window), 0);
					v.yellowSquare[1]->Position = glm::vec2(-*d.tileSize, -*d.tileSize);
					//printBoard();
					break;
				}
				else // clicked somewhere else on board
				{
					if (v.redSquares.size() > 0) v.redSquares.clear();
					//if (legalSquareDots.size() > 0) legalSquareDots.clear();
				}

		// move piece in real time (dragging)
		if (*d.selected != -1)
			v.object[*d.selected]->Position = glm::vec2(getMousePos(window) - *d.tileSize / 2);
	}
}

void GL::dragPieceRelease(GLFWwindow* window)
{
	if (d.movingPiece) // option 1: clicking and dragging
	{
		// place piece in correct place when release
		bool movedProperly = false;
		// reset avaible moves, if moved
		for (int i = 0; i < d.legalSquares->size(); i++)
			if (getSquarePos(window) == d.legalSquares[0][i])
			{
				movedProperly = true;
				placePieceOnNewSquare(window, i);
				v.placeJellowSquare(window, getSquarePos(window), 1);
			}

		// if piece dragged on unavaiable square (dont let that)
		if (!movedProperly)
		{
			v.object[*d.selected]->Position.x = d.originalSquarePos.x * *d.tileSize;
			v.object[*d.selected]->Position.y = d.originalSquarePos.y * *d.tileSize;
		}

		// reset selection and tur of piece dragging
		*d.selected = -1;
		d.movingPiece = false;
	}
}

void GL::placePieceOnNewSquare(GLFWwindow* window, int& iterator)
{
	// place piece in correct square
	v.object[*d.selected]->Position.x = getSquarePos(window).x * *d.tileSize;
	v.object[*d.selected]->Position.y = getSquarePos(window).y * *d.tileSize;

	// remove (hide, not remove :D) opponent piece
	for (int j = 0; j < 32; j++)
		if (v.object[*d.selected]->Position == v.object[j]->Position && *d.selected != j)
			v.object[j]->Position = glm::vec2(-*d.tileSize, -*d.tileSize);

	// update layout (for debbuging later)
	glm::vec2 p = d.getSquareLayoutPos(v.object[iterator]->Position);
	d.board[getSquarePos(window).y][getSquarePos(window).x] = v.object[*d.selected]->pieceRef;
	d.board[d.originalSquarePos.y][d.originalSquarePos.x] = 0;

	v.legalSquareDots.clear();
	d.legalSquares->clear();
	d.whiteToMove = !d.whiteToMove;

	// if move has been made
	//moveCount++;
}

void GL::clickPlaceSquare(GLFWwindow* window)
{
	if (d.legalSquares->size() > 0)
		for (int i = 0; i < d.legalSquares->size(); i++)
			if (getSquarePos(window).x == v.legalSquareDots[i]->Position.x / *d.tileSize &&
				getSquarePos(window).y == v.legalSquareDots[i]->Position.y / *d.tileSize)
			{
				// piece animation
				animatedPiece = d.selectedSaved;
				saveDirectionVector(d.originalSquarePos, getSquarePos(window));
				PieceAnimation = true;

				// update layout (for debbuging later)
				d.board[getSquarePos(window).y][getSquarePos(window).x] = v.object[d.selectedSaved]->pieceRef;
				d.board[d.originalSquarePos.y][d.originalSquarePos.x] = 0;

				// reset selection
				v.legalSquareDots.clear();
				d.legalSquares->clear();
				d.whiteToMove = !d.whiteToMove;
				d.selectedSaved = -1;
			}
}


// Basic uttilities functions
glm::vec2 GL::getMousePos(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return glm::vec2(x, y);
}

glm::ivec2 GL::getSquarePos(GLFWwindow* window)
{
	return glm::ivec2(
		(getMousePos(window).x / *d.tileSize),
		(getMousePos(window).y / *d.tileSize));
}

bool GL::areTouching(GLFWwindow* window, GameObject* object)
{
	if (getMousePos(window).x > object->Position.x &&
		getMousePos(window).x < object->Position.x + object->Size.x &&
		getMousePos(window).y > object->Position.y &&
		getMousePos(window).y < object->Position.y + object->Size.y)
		return true;
	else
		return false;
}


// TODO: move

void GL::createRedSuqare(GLFWwindow* window)
{
	v.redSquares.push_back(new GameObject(
		glm::vec2(
			getSquarePos(window).x * *d.tileSize,
			getSquarePos(window).y * *d.tileSize),
		glm::vec2(*d.tileSize),
		ResourceManager::GetTexture("tile"),
		glm::vec4(1.0f, 0.0f, 0.0f, 0.5f)));
}

void GL::updateRedSquares(GLFWwindow* window)
{
	bool squareIsFree = true;

	// check if selected square allready is red
	for (int i = 0; i < v.redSquares.size(); i++)
		if (areTouching(window, v.redSquares[i]))
		{
			// if it is red, delete it and do not allow to color it
			v.redSquares.erase(v.redSquares.begin() + i);
			squareIsFree = false;
		}

	// if it is not red, than color it
	if (squareIsFree) createRedSuqare(window);
}

void GL::animatePiece(GLFWwindow* window)
{
	if (PieceAnimation) animCounter++;
	if (animCounter >= 1)
	{
		// place/remove jellow, red squares
		if (animCounter == 1)
		{
			v.placeJellowSquare(window, newPos, 1);
			if (v.redSquares.size() > 0) v.redSquares.clear();
		}

		v.object[animatedPiece]->Position.x += PieceMoveSpeed.x;
		v.object[animatedPiece]->Position.y += PieceMoveSpeed.y;

		// stop Application and reset Application frame counter
		if (animCounter == animFPS)
		{
			// place square in correct position
			v.object[animatedPiece]->Position.x = newPos.x * *d.tileSize;
			v.object[animatedPiece]->Position.y = newPos.y * *d.tileSize;

			// if it is occupied by opponent's piece, remove opponentes piece
			for (int j = 0; j < 32; j++)
				if (v.object[animatedPiece]->Position == v.object[j]->Position && animatedPiece != j)
					v.object[j]->Position = glm::vec2(-*d.tileSize, -*d.tileSize);
			PieceAnimation = false;
			animCounter = 0;

		}
	}
}

void GL::saveDirectionVector(glm::ivec2 oP, glm::ivec2 nP)
{
	// save new Position
	newPos.x = nP.x;
	newPos.y = nP.y;

	// difference between pieces (in pixels)
	glm::vec2 dif;
	dif.x = (newPos.x * *d.tileSize - oP.x * *d.tileSize);
	dif.y = (newPos.y * *d.tileSize - oP.y * *d.tileSize);

	//totalMag = abs(mag);
	PieceMoveSpeed.x = dif.x / animFPS;
	PieceMoveSpeed.y = dif.y / animFPS;
}

