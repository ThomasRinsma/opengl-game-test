#include "shaderprogram.ih"

GLuint ShaderProgram::uniform(std::string const &uniformName) const
{
	if (d_uniforms.find(uniformName) != d_uniforms.end())
		return d_uniforms.at(uniformName);
	
	return glGetUniformLocation(d_shaderProgram, uniformName.c_str());
}