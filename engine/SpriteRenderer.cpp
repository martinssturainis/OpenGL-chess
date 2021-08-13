#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const Shader& shader)
{
	this->shader = shader;
	initialize();
}

void SpriteRenderer::drawSprite(Textured2D texture, glm::vec2 pos, glm::vec2 size,glm::vec4 color)
{
	this->shader.use();

	// init transformation matrix for postition and scale
	glm::mat4 model = glm::mat4(1.0f); 
	// init position. Tagad, lai pavrvietotu pietiks ar vec2 pos(x,y). z vienmer bus 0, jo stradajam ar 2d
	model = glm::translate(model, glm::vec3(pos, 0.0f)); 
	// init scale. Tagad, lai mainitu izmerus, pietiks ar vec2 size(x,y)
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f)); 
	
	// send uni data to shader
	shader.sendMatrix4fv("model", model); 
	shader.sendFloat4fv("newColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRenderer::initialize()
{
	// 2 trissturi, lai izveidotu 1 cetrsturi. Pietiktu ar 4 punktiem, bet es biju parak slinks, lai rakstītu indices
	GLfloat vertices[] =
	{
		// pos      // uv texture corrd
		0.0f, 1.0f,  0.0f, 1.0f,
		1.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,

		0.0f, 1.0f,  0.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 0.0f,  1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

