#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shaderprogram.h"

using namespace std;

string const vertPostfix = "/vertex.shader";
string const fragPostfix = "/fragment.shader";

std::string const fragDataName = "outColor";

ShaderProgram::ShaderProgram(string const &shaderPath)
{
	loadShaders(shaderPath + vertPostfix, shaderPath + fragPostfix);
	linkShaders();
}

void ShaderProgram::use() const
{
	glUseProgram(d_shaderProgram);
}

void ShaderProgram::loadShaders(string const &vertPath, string const &fragPath)
{
	// Load the files into ifstreams
	ifstream vertexFile(vertPath);
	ifstream fragmentFile(fragPath);

	// insert the ifstreams' streambufs into ostringstreams
	ostringstream vertStringStream, fragStringStream;
	vertStringStream << vertexFile.rdbuf();
	fragStringStream << fragmentFile.rdbuf();

	// Create the shader references
	d_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	d_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrieve strings
	string vertString = vertStringStream.str();
	string fragString = fragStringStream.str();

	// Temporary C-strings
	GLchar const *vertCString = reinterpret_cast<GLchar const *>(vertString.c_str());
	GLchar const *fragCString = reinterpret_cast<GLchar const *>(fragString.c_str());


	// Compile them
	GLint status;
	glShaderSource(d_vertexShader, 1, &vertCString, NULL);
	glCompileShader(d_vertexShader);
	glGetShaderiv(d_vertexShader, GL_COMPILE_STATUS, &status); 
	if (status != GL_TRUE)
	{
		cerr << "Vertex shader failed to compile:\n";
		char buffer[512];
		glGetShaderInfoLog(d_vertexShader, 512, NULL, buffer);
		cerr << buffer << endl;
		throw string("error while compiling vertex shader");
	}

	glShaderSource(d_fragmentShader, 1, &fragCString, NULL);
	glCompileShader(d_fragmentShader);
	glGetShaderiv(d_fragmentShader, GL_COMPILE_STATUS, &status); 
	if (status != GL_TRUE)
	{
		cerr << "Fragment shader failed to compile:\n";
		char buffer[512];
		glGetShaderInfoLog(d_fragmentShader, 512, NULL, buffer);
		cerr << buffer << endl;;
		throw string("error while compiling fragment shader");
	}

	// Create the shader program
	d_shaderProgram = glCreateProgram();
	
	glAttachShader(d_shaderProgram, d_vertexShader);
	glAttachShader(d_shaderProgram, d_fragmentShader);
}

void ShaderProgram::linkShaders()
{
	glBindFragDataLocation(d_shaderProgram, 0, fragDataName.c_str());

	// Link the shader program
	glLinkProgram(d_shaderProgram);
}

GLuint ShaderProgram::attribute(string const &attributeName)
{
	if (d_attributes.find(attributeName) != d_attributes.end())
		return d_attributes.at(attributeName);
	
	GLint attr = glGetAttribLocation(d_shaderProgram, attributeName.c_str());
	
	// The attribute does not exist
	if (attr == -1)
		throw string("invalid attribute requested: '" + attributeName + "'");

	// Cache and return the attribute
	d_attributes[attributeName] = attr;
	return attr;
}

GLuint ShaderProgram::uniform(string const &uniformName)
{
	if (d_uniforms.find(uniformName) != d_uniforms.end())
		return d_uniforms.at(uniformName);

	GLint uni = glGetUniformLocation(d_shaderProgram, uniformName.c_str());
	
	// The uniform does not exist
	if (uni == -1)
		throw string("invalid uniform requested: '" + uniformName + "'");

	// Cache and return the uniform
	d_uniforms[uniformName] = uni;
	return uni;
}