#include "Textured2D.h"

Textured2D::Textured2D() : ImageColor(0)
{
	glGenTextures(1, &ID);
}

void Textured2D::generate(const char* imageSource, bool Alpha)
{
	ImageColor = (Alpha == true) ? GL_RGBA : GL_RGB;

	int width, height, colors;
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(imageSource, &width, &height, &colors, 0);

	glBindTexture(GL_TEXTURE_2D, ID);
		
	if (!data) 
		std::cout << "image loading error" << std::endl;
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, ImageColor, width, height, 0, ImageColor, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}

void Textured2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
