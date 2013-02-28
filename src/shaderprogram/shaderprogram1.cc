#include "shaderprogram.ih"

string const vertPostfix = "/vertex.shader";
string const fragPostfix = "/fragment.shader";
string const uniPostfix = "/uniforms.txt";

ShaderProgram::ShaderProgram(string const &shaderPath)
{
	// TODO: exceptions instead of flag
	d_error = not loadShaders(shaderPath + vertPostfix,
							shaderPath + fragPostfix);

	vector<string> uniformNames;

	ifstream uniformsFile(shaderPath + uniPostfix);
	while (uniformsFile)
	{
		string name;
		getline(uniformsFile, name);
		uniformNames.push_back(name);
	}

	if (not d_error)
		linkShaders(uniformNames);
}
