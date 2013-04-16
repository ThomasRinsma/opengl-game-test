#include "shaderprogram.ih"

std::string const fragDataName = "outColor";

void ShaderProgram::linkShaders()
{
	glBindFragDataLocation(d_shaderProgram, 0, fragDataName.c_str());

	// Link the shader program
	glLinkProgram(d_shaderProgram);
}