#include "Shader.h"

Shader::Shader() 
	: ID(0)
{
}

void Shader::generate(const char* vertexSource, const char* fragmentSource)
{
	std::string convertedV = convert(vertexSource);
	std::string convertedF = convert(fragmentSource);

	const char* vSource = convertedV.c_str();
	const char* fSource = convertedF.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vSource, NULL);
	glCompileShader(vertex);
	checkForErrors(vertex, "VERTEX");

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fSource, NULL);
	glCompileShader(fragment);
	checkForErrors(vertex, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkForErrors(vertex, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::sendInt(const char* unifName, int value)
{
	glUniform1i(glGetUniformLocation(ID, unifName), value);
}

void Shader::sendFloat3fv(const char* unifName, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(ID, unifName),1, &value[0]);
}

void Shader::sendFloat4fv(const char* unifName, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(ID, unifName),1, &value[0]);
}

void Shader::sendMatrix4fv(const char* unifName, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, unifName), 1, GL_FALSE, &matrix[0][0]);
}
std::string Shader::convert(const char* fileSource)
{
	std::ifstream in(fileSource, std::ios::binary);
	if (in)
	{
		std::string output;
		in.seekg(0, std::ios::end);
		output.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&output[0], output.size());
		in.close();
		return output;
	}
}

void Shader::checkForErrors(GLuint source, std::string type)
{
	GLint SUCCESS;
	GLchar LOG[1024];

	if (type == "VERTEX" || type == "FRAGMENT")
	{
		glGetShaderiv(source, GL_COMPILE_STATUS, &SUCCESS);
		if (!SUCCESS)
		{
			glGetShaderInfoLog(source, 1024, NULL, LOG);
			std::cout << "ERROR: " << type << " error. \n" << LOG << std::endl;
		}
	}
	else if (type == "PROGRAM")
	{
		glGetShaderiv(source, GL_LINK_STATUS, &SUCCESS);
		if (!SUCCESS)
		{
			glGetShaderInfoLog(source, 1024, NULL, LOG);
			std::cout << "ERROR: " << type << " error. \n" << LOG << std::endl;
		}
	}
	else std::cout << "Error checking spelling mistake in Shader.cpp" << std::endl;
}
