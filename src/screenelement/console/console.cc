#include "console.ih"

Console::Console(Controller const &controller)
:
	ScreenElement(ResourceManager::instance().shaderProgram("simpleColor")),
	d_controller(controller),
	d_consoleDown(false),
	d_toggleKeyDown(false)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Console background vertices:   X, Y, Z,  R, G, B
	float vertices[] = {
		0.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		0.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		0.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram.attribute("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}