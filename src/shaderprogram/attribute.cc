#include "shaderprogram.ih"

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