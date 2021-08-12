#pragma once
#include "GL.h" // Game Logic

class Application
{
public: 
	// main
	Application();
	bool running();
	void play();

private:
	
	// initialising
	void initialize();
	void initOpenGL();
	void initShaders();
	
	//updating
	void update(GLFWwindow* window);
	
	//rendering
	void render();
	
	// window data
	GLFWwindow* window;
	unsigned int scrWidth, scrHeight;
	
	// OpengGL renderer
	SpriteRenderer* renderer;
	
	// All game logic and visuals entity data
	GL gl;
};
