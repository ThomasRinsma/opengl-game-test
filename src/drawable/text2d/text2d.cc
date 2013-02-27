#include "text2d.ih"

string const fontPath = "textures/font.bmp"; // TODO: fix this constant

Text2D::Text2D(ShaderProgram &shaderProgram, glm::vec2 const &position, glm::vec2 const &scale, string const &text)
:
	Drawable(shaderProgram),
	d_position(position),
	d_text(text)
{
	d_modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(d_position, 0.0f));
	d_modelMat = glm::scale(d_modelMat, glm::vec3(scale, 1.0f));

	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	float vertices[] = {
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f,   1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,   0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,
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
	if (not texImage.loadFromFile(fontPath))
	{
		cerr << "Error loading font texture from file\n";
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		texImage.getSize().x, texImage.getSize().y, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texImage.getPixelsPtr());

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
