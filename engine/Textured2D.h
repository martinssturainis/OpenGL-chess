#pragma once
#include<iostream>
#include<stb/stb_image.h>
#include<glad/glad.h>

class Textured2D
{
public:
	Textured2D();
	void generate(const char* imageSource, bool Alpha);
	void bind() const;
	GLuint ID;
	GLuint ImageColor;
};

