#include "shaderprogram.ih"

string const shaderPath = "shaders/";
string const vertPostfix = "/vertex.shader";
string const fragPostfix = "/fragment.shader";

ShaderProgram::ShaderProgram(string const &shaderName, vector<string> const &uniformNames)
{
	d_error = not loadShaders(shaderPath + shaderName + vertPostfix,
							shaderPath + shaderName + fragPostfix);

	if (not d_error)
		linkShaders(uniformNames);
}
