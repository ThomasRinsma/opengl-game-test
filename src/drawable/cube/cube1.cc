#include "cube.ih"

const string texPath = "textures/texture.png";

Cube::Cube(glm::vec3 position, ShaderProgram *shaderProgram)
:
	Drawable(position, shaderProgram)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Cube vertices:   X, Y, Z,   U, V
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram->attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	// Link array buffer to "texcoord" attribute
	GLint texAttrib = d_shaderProgram->attribLocation("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Load texture
	glGenTextures(1, &d_tex);
	glBindTexture(GL_TEXTURE_2D, d_tex);

	sf::Image texImage;
	if (not texImage.LoadFromFile(texPath))
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


	glEnable(GL_DEPTH_TEST);
}