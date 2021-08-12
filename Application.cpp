#include "Application.h"

std::map<std::string, Shader>		ResourceManager::myShaders;
std::map<std::string, Textured2D>	ResourceManager::myTextures;

// main functions
Application::Application()
	: scrWidth(800), scrHeight(800), gl(window, scrWidth, scrHeight)
{
	initOpenGL();
	initialize();
}

bool Application::running()
{
	return !glfwWindowShouldClose(window);
}

void Application::play()
{
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	update(window);
	render();
	glfwSwapBuffers(window);
}

// initialising
void Application::initialize()
{
	initShaders();
	gl.initveryThing();
}

void Application::initOpenGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_PROFILE);

	window = glfwCreateWindow(scrWidth, scrHeight, "Testing openGL Maths", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1);

	glViewport(0, 0, scrWidth, scrHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::initShaders()
{
	// Shader and renderer
	ResourceManager::GenerateNewShader("default", "vertex.shader", "fragment.shader");
	renderer = new SpriteRenderer(ResourceManager::GetShader("default"));

	// passing variables to shader
	ResourceManager::GetShader("default").use();
	glm::mat4 projection = glm::ortho(0.0f, (float)(scrWidth), (float)(scrHeight), 0.0f, 0.0f, 0.1f);
	ResourceManager::GetShader("default").sendMatrix4fv("projection", projection);
	ResourceManager::GetShader("default").sendInt("image", 0);
}

// updating
void Application::update(GLFWwindow* window)
{
	gl.updateGameLogic(window);
}

//rendering
void Application::render()
{
	gl.drawEveryThing(renderer);
}