#include "ResourceManager.h"

Shader ResourceManager::GenerateNewShader(std::string mapName, const char* vertexSource, const char* fragmentSource)
{
	myShaders[mapName] = loadShaderFromFile(vertexSource, fragmentSource);
	return myShaders[mapName];
}

Shader ResourceManager::GetShader(std::string mapName)
{
	return myShaders[mapName];
}

Textured2D ResourceManager::GenerateNewTexture(std::string mapName, const char* imageSource, bool Alpha)
{
	myTextures[mapName] = loadTextureFromile(imageSource, Alpha);
	return myTextures[mapName];
}

Textured2D ResourceManager::GetTexture(std::string mapName)
{
	return myTextures[mapName];
}

Shader ResourceManager::loadShaderFromFile(const char* vertexSource, const char* fragmentSource)
{
	Shader newShader;
	newShader.generate(vertexSource, fragmentSource);
	return newShader;
}

Textured2D ResourceManager::loadTextureFromile(const char* imageSource, bool Alpha)
{
	Textured2D newTexture;
	newTexture.generate(imageSource, Alpha);
	return newTexture;
}
