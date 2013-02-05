#include "text.ih"

string const fontPath = "textures/font.bmp"; // TODO: fix this constant

Text::Text(ShaderProgram &shaderProgram, string const &text)
:
	SceneObject(shaderProgram),
	d_text(text)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	float vertices[] = {
		-0.1f, -0.1f, 0.0f,   0.0f, 1.0f,
		 0.1f, -0.1f, 0.0f,   1.0f, 1.0f,
		 0.1f,  0.1f, 0.0f,   1.0f, 0.0f,
		 0.1f,  0.1f, 0.0f,   1.0f, 0.0f,
		-0.1f,  0.1f, 0.0f,   0.0f, 0.0f,
		-0.1f, -0.1f, 0.0f,   0.0f, 1.0f,
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint texAttrib = d_shaderProgram.attribLocation("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Make texture
	glGenTextures(1, &d_tex);
	glBindTexture(GL_TEXTURE_2D, d_tex);

	sf::Image texImage;
	if (not texImage.LoadFromFile(fontPath))
	{
		cerr << "Error loading font texture from file\n";
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		texImage.GetWidth(), texImage.GetHeight(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texImage.GetPixelsPtr());

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
