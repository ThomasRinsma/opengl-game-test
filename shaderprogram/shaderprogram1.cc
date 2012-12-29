#include "shaderprogram.ih"

ShaderProgram::ShaderProgram(std::string vertPath, std::string fragPath, 
        	vector<std::string> uniformNames)
{
	d_error = not loadShaders(vertPath, fragPath);

	cout << "Error: " << d_error << endl;

	if (not d_error)
		linkShaders(uniformNames);
}
