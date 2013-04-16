#include "shaderprogram.ih"

string const vertPostfix = "/vertex.shader";
string const fragPostfix = "/fragment.shader";

ShaderProgram::ShaderProgram(string const &shaderPath)
{
	loadShaders(shaderPath + vertPostfix, shaderPath + fragPostfix);
	linkShaders();
}
