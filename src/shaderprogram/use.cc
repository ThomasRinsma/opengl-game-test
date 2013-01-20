#include "shaderprogram.ih"

void ShaderProgram::use() const
{
	glUseProgram(d_shaderProgram);
}