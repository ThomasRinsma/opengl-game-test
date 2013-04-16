#include "text.ih"

string const fontTexName = "font";
string const requiredShader = "simpleText";

Text::Text(string const &text)
:
	DrawableEntity(ResourceManager::instance().shaderProgram(requiredShader)),
	d_texture(ResourceManager::instance().texture(fontTexName)),
	d_text(text)
{
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
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint texAttrib = d_shaderProgram.attribute("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	d_texture.bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
