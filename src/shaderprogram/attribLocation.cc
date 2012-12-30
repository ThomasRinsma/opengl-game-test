#include "shaderprogram.ih"

GLuint ShaderProgram::attribLocation(std::string const &attrName)
{
	return glGetAttribLocation(d_shaderProgram, attrName.c_str());
}