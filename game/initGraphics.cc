#include "game.ih"

const string vertPath = "game/shaders/vertex.shader";
const string fragPath = "game/shaders/fragment.shader";

const string texPath = "game/textures/texture.png";

void Game::initGraphics()
{
	// Load shaders
	if (not loadShaders(vertPath, fragPath))
	{
		d_running = false;
		return;
	}

	// Set up matrix uniforms
	d_modelMatRef = glGetUniformLocation(d_shaderProgram, "model");
	d_viewMatRef = glGetUniformLocation(d_shaderProgram, "view");
	d_projMatRef = glGetUniformLocation(d_shaderProgram, "proj");

	d_viewMat = lookAt(
		vec3(0.0f, 1.0f, 5.0f), // Look from y+, z+
		vec3(0.0f, 0.0f, 0.0f), // Look down at (0,0,0)
		vec3(0.0f, 1.0f, 0.0f)  // y+ is up
	);

	d_projMat = perspective(
		45.0f,	// 45 degree FOV
		static_cast<float>(d_win->GetWidth()) /
		static_cast<float>(d_win->GetHeight()),  // Ratio
		1.0f, 10.0f // near/far
	);


	// Create a VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a VBO
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

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
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

/*
	// Create element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	// Square consists of two triangles
	GLuint elements[] = {
		
	};

	// Copy element data into EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

*/

	// Link array buffer to "position" attribute
	GLint posAttrib = glGetAttribLocation(d_shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	// Link array buffer to "texcoord" attribute
	GLint texAttrib = glGetAttribLocation(d_shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Load texture
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	Image texImage;
	if (not texImage.LoadFromFile(texPath))
	{
		d_running = false;
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