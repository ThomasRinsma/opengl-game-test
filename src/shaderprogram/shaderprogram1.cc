#include "shaderprogram.ih"

string const vertPostfix = "/vertex.shader";
string const fragPostfix = "/fragment.shader";
string const uniPostfix = "/uniforms.txt";

ShaderProgram::ShaderProgram(string const &shaderPath)
{
	loadShaders(shaderPath + vertPostfix, shaderPath + fragPostfix);

	vector<string> uniformNames;

	ifstream uniformsFile(shaderPath + uniPostfix);
	while (uniformsFile)
	{
		string name;
		getline(uniformsFile, name);
		uniformNames.push_back(name);
	}

	linkShaders(uniformNames);
}
