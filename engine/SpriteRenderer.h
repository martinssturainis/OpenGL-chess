#pragma once
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	void drawSprite(Textured2D texture, glm::vec2 pos, glm::vec2 size, glm::vec4 color);
	void initialize();
private:
	Shader shader;
	GLuint VAO, VBO;
};

