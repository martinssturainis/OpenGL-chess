#include "Visuals.h"


Visuals::Visuals(float* tSize, int* slt, std::vector <bool>* lgType, std::vector<glm::ivec2>* lgS)
	:tileSize(tSize), selected(slt), lgType(lgType), legalSquares(lgS)
{
}

void Visuals::renderBoard(SpriteRenderer* renderer)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardSquare[i][j]->Draw(*renderer);

	// draw jellow square
	for (int i = 0; i < 2; i++)
		yellowSquare[i]->Draw(*renderer);

	// draw red squares
	if (redSquares.size() > 0)
		for (int i = 0; i < redSquares.size(); i++)
			redSquares[i]->Draw(*renderer);

	// draw pieces
	for (int i = 0; i < 32; i++) object[i]->Draw(*renderer);

	// draw avaible move dots
	for (int i = 0; i < legalSquareDots.size(); i++)
		legalSquareDots[i]->Draw(*renderer);
}

void Visuals::initVisuals(int board[8][8])
{
	setPieces(board);
	setBoard();
	setAttributes();
}

void Visuals::setPieces(int board[8][8])
{
	int ojbjectNumber = 0;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != 0)
			{
				// gets texture name
				std::string fileName = "textures/pieces/" + std::to_string(board[i][j]) + ".png";

				// generates texture
				ResourceManager::GenerateNewTexture("piece_" + std::to_string(board[i][j]), fileName.c_str(), true);

				// generates object with made parameters: size and position
				object[ojbjectNumber] = new GameObject(
					glm::vec2(j * *tileSize, i * *tileSize), //position
					glm::vec2(*tileSize),						 //size
					ResourceManager::GetTexture("piece_" + std::to_string(board[i][j])));    //texture

				// give piece a reference number
				object[ojbjectNumber]->pieceRef = (piece)(board[i][j]);

				ojbjectNumber++;
			}
}

void Visuals::setAttributes()
{
	// yellow square (one)
	for (int i = 0; i < 2; i++)
		yellowSquare[i] = new GameObject(
			glm::vec2(-*tileSize),				 //position
			glm::vec2(*tileSize), 				 //size
			ResourceManager::GetTexture("tile"), //texture
			glm::vec4(1.1f, 1.1f, 0.0f, 0.55f)); //color

	// texture for dots (avaible moves)
	ResourceManager::GenerateNewTexture("dot0", "textures/pieces/transparentTile.png", true);
	ResourceManager::GenerateNewTexture("dot1", "textures/pieces/transparentRoundTile.png", true);
}

void Visuals::setBoard()
{
	ResourceManager::GenerateNewTexture("tile", "textures/pieces/tileWhite.png", true);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((i + j) % 2 != 0) // black piece
				boardSquare[i][j] = new GameObject(
					glm::vec2(j * *tileSize, i * *tileSize), //position
					glm::vec2(*tileSize),				   //size
					ResourceManager::GetTexture("tile"),   //texture
					glm::vec4(0.41f, 0.60f, 0.25f, 1.0f)); //color
			else // white piece
				boardSquare[i][j] = new GameObject(
					glm::vec2(j * *tileSize, i * *tileSize), //position
					glm::vec2(*tileSize),				   //size
					ResourceManager::GetTexture("tile"),   //texture
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));	   //color
	std::cout << sizeof(ResourceManager::GetTexture("tile")) << std::endl;   //texture
} 

// realtime updates

void Visuals::createAvaibleMoveDots(std::vector<glm::ivec2>& ls, std::vector<bool>& lgT)
{
	// ls: legal squares, lgT: legal square type 
	legalSquareDots.clear();
	for (int i = 0; i < ls.size(); i++)
	{
		avaibleMove = new GameObject(
			glm::vec2(ls[i].x * *tileSize, ls[i].y * *tileSize),//position
			glm::vec2(*tileSize), 								//size
			ResourceManager::GetTexture("dot" + std::to_string(lgT[i])), //texture
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));					//color

		legalSquareDots.push_back(avaibleMove);
	}
}

void Visuals::showAvaibleMoves(GLFWwindow* window, std::vector<glm::ivec2>& ls, std::vector<bool>& lgT,
	glm::ivec2 sqPos, int board[8][8])
{
	//reset avaible moves
	ls.clear();
	lgT.clear();

	switch (object[*selected]->pieceRef)
	{
	case(R): case(r):
		Move::rook(ls, lgT, sqPos, board); break;
	case(N): case(n):
		Move::knight(ls, lgT, sqPos, board); break;
	case(B): case(b):
		Move::bishop(ls, lgT, sqPos, board); break;
	case(Q): case(q):
		Move::queen(ls, lgT, sqPos, board); break;
	case(K): case(k):
		Move::king(ls, lgT, sqPos, board); break;
	case(P):
		Move::downPawn(ls, lgT, sqPos, board); break;
	case(p):
		Move::upPawn(ls, lgT, sqPos, board); break;
	}

	// create avaiable moves
	createAvaibleMoveDots(ls, lgT);
}

void Visuals::placeJellowSquare(GLFWwindow* window, glm::ivec2 position, int i)
{
	yellowSquare[i]->Position.x = position.x * *tileSize;
	yellowSquare[i]->Position.y = position.y * *tileSize;

}
