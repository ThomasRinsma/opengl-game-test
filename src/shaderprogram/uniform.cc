#include "shaderprogram.ih"

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