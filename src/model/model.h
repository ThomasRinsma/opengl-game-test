#ifndef INCLUDED_MODEL_
#define INCLUDED_MODEL_

#include <vector>
#include <string>
#include <GL/gl.h>
#include "../shaderprogram/shaderprogram.h"

class Model
{
	GLuint d_vbo;
	GLuint d_vao;

	std::vector<float> d_verts;
	size_t d_numVerts;

    public:
        Model(std::string const &path);
        ~Model();

        void draw() const;
    	void initAttributes(ShaderProgram &shaderProgram);

    private:
    	void loadModel(std::string const &path);
};
        
#endif
