#include "shaderprogram.ih"

void ShaderProgram::use()
{
	glUseProgram(d_shaderProgram);
}