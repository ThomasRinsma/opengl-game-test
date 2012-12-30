#include "grid.ih"

Grid::Grid(glm::vec3 position, ShaderProgram *shaderProgram)
:
	Drawable(position, shaderProgram)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

/*
	// Grid vertices:   X, Y, Z,   R, G, B
	float vertices[] = {
		-10.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		 10.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, -10.0f,  1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f,  10.0f,  1.0f, 0.0f, 0.0f,
		// TODO actual grid
	};
*/
	vector<float> vertVec;
	for (int x = -10; x <= 10; ++x)
	{
		vertVec.insert(vertVec.end(), {(float)x, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f});
		vertVec.insert(vertVec.end(), {(float)x, 0.0f,  10.0f, 1.0f, 0.0f, 0.0f});
	}

	for (int z = -10; z <= 10; ++z)
	{
		vertVec.insert(vertVec.end(), {-10.0f, 0.0f, (float)z, 1.0f, 0.0f, 0.0f});
		vertVec.insert(vertVec.end(), { 10.0f, 0.0f, (float)z, 1.0f, 0.0f, 0.0f});
	}


	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertVec.size() * sizeof(float), vertVec.data(), GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram->attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram->attribLocation("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

	//glEnable(GL_DEPTH_TEST);
}
