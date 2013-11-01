#ifndef INCLUDED_MODEL_
#define INCLUDED_MODEL_

#include <vector>
#include <string>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "shaderprogram.h"

class Model
{
	struct WavefrontObject
	{
		GLuint vbo;
		GLuint vao;

		std::string name; 

		std::vector<glm::vec3> verts;
		std::vector<glm::vec3> norms;
		std::vector<glm::vec2> texcoords;
		
		std::vector<float> vboArray;
	};

	std::vector<WavefrontObject> d_objects;

	public:
		Model(std::string const &path);
		~Model();

		void draw() const;
		void initAttributes(ShaderProgram &shaderProgram);

	private:
		void loadModel(std::string const &path);

		// helper for loadModel
		void insertVertices(std::vector<size_t> indices, int *vertIdx, int *texIdx, int *normIdx);
};
		
#endif