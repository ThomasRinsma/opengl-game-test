#include "shaderprogram.ih"

GLuint ShaderProgram::attribLocation(std::string const &attrName) const
{
	return glGetAttribLocation(d_shaderProgram, attrName.c_str());
}