#include "shaderprogram.ih"

GLuint ShaderProgram::attribute(std::string const &attributeName) const
{
	if (d_attributes.find(attributeName) != d_attributes.end())
		return d_attributes.at(attributeName);
	
	return glGetAttribLocation(d_shaderProgram, attributeName.c_str());
}