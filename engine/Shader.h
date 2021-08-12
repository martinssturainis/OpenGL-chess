#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

class Shader
{
public:
	Shader();
	void generate(const char* vertexSource, const char* fragmentSource);
	void use() const;

	void sendInt(const char*, int value);
	void sendFloat3fv(const char* unifName, glm::vec3 value);
	void sendFloat4fv(const char* unifName, glm::vec4 value);
	void sendMatrix4fv(const char* unifName, glm::mat4 matrix);

	GLuint ID;
private:
	std::string convert(const char* fileSource);
	void checkForErrors(GLuint source, std::string type);
};