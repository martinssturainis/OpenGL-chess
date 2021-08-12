#pragma once
#include<map>
#include "Textured2D.h"
#include "Shader.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> myShaders;
	static std::map<std::string, Textured2D> myTextures;

	// generate entities
	static Textured2D GenerateNewTexture(std::string mapName, const char* imageSource, bool Alpha);
	static Shader GenerateNewShader(std::string mapName, const char* vertexSource, const char* fragmentSource);

	// get entities
	static Textured2D GetTexture(std::string mapName);
	static Shader GetShader(std::string mapName);

private:
	// load entities from files and .h files
	static Shader loadShaderFromFile(const char* vertexSource, const char* fragmentSource);
	static Textured2D loadTextureFromile(const char* imageSource, bool Alpha);

};

