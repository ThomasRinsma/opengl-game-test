#include "game.ih"

bool Game::loadShaders(string vertPath, string fragPath)
{
	// Load the files into ifstreams
	ifstream vertexFile(vertPath);
	ifstream fragmentFile(fragPath);

	// insert the ifstreams' streambufs into ostringstreams
	ostringstream vertStringStream, fragStringStream;
	vertStringStream << vertexFile.rdbuf();
	fragStringStream << fragmentFile.rdbuf();

	// Create the shader references
	d_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	d_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrieve strings
	string vertString = vertStringStream.str();
	string fragString = fragStringStream.str();

	// Temporary C-strings
	GLchar const *vertCString = reinterpret_cast<GLchar const *>(vertString.c_str());
	GLchar const *fragCString = reinterpret_cast<GLchar const *>(fragString.c_str());


	// Compile them
	GLint status;
	glShaderSource(d_vertexShader, 1, &vertCString, NULL);
	glCompileShader(d_vertexShader);
	glGetShaderiv(d_vertexShader, GL_COMPILE_STATUS, &status); 
	if (status != GL_TRUE)
	{
		cerr << "Vertex shader failed to compile:\n";
		char buffer[512];
		glGetShaderInfoLog(d_vertexShader, 512, NULL, buffer);
		cerr << buffer << endl;
		return false;
	}

	glShaderSource(d_fragmentShader, 1, &fragCString, NULL);
	glCompileShader(d_fragmentShader);
	glGetShaderiv(d_fragmentShader, GL_COMPILE_STATUS, &status); 
	if (status != GL_TRUE)
	{
		cerr << "Fragment shader failed to compile:\n";
		char buffer[512];
		glGetShaderInfoLog(d_fragmentShader, 512, NULL, buffer);
		cerr << buffer << endl;;
		return false;
	}

	// Create the shader program
	d_shaderProgram = glCreateProgram();
	glAttachShader(d_shaderProgram, d_vertexShader);
	glAttachShader(d_shaderProgram, d_fragmentShader);

	glBindFragDataLocation(d_shaderProgram, 0, "outColor");

	// Link and use the shader program
	glLinkProgram(d_shaderProgram);
	glUseProgram(d_shaderProgram);

	return true;
}