#include "portal.ih"

Portal::Portal(ShaderProgram &shaderProgram, Entity *destination)
:
	SceneObject(shaderProgram),
	d_destination(destination)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Portal vertices:   X, Y, Z
	float vertices[] = {
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram.attribLocation("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}
