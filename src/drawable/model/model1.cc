#include "model.ih"

string const modelPrefix = "models/";
string const texPrefix   = "textures/";

string const modelPostfix = ".obj";
string const texPostfix   = ".png";

Model::Model(ShaderProgram *shaderProgram, string const &texName, string const &modelName)
:
	Drawable(shaderProgram)
{
	loadModel(modelPrefix + modelName + modelPostfix);

	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, d_verts.size() * sizeof(float), d_verts.data(), GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram->attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLint normAttrib = d_shaderProgram->attribLocation("normal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));

	// Link array buffer to "texcoord" attribute
	GLint texAttrib = d_shaderProgram->attribLocation("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

	// Load texture
	glGenTextures(1, &d_tex);
	glBindTexture(GL_TEXTURE_2D, d_tex);

	sf::Image texImage;
	if (not texImage.LoadFromFile(texPrefix + texName + texPostfix))
	{
		cerr << "Error loading texture from file\n";
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		texImage.GetWidth(), texImage.GetHeight(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texImage.GetPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
