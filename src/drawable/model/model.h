#ifndef INCLUDED_MODEL_
#define INCLUDED_MODEL_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Model : public Drawable
{
	GLuint d_vao;
	GLuint d_vbo;
	GLuint d_tex;
	std::vector<float> d_verts;
	size_t d_numVerts;

    public:
        Model(glm::vec3 position, ShaderProgram *shaderProgram, std::string const &texName, std::string const &modelName);

    private:
    	virtual void drawImpl(glm::mat4 &viewMat, glm::mat4 &projMat);
    	void loadModel(std::string const &modelPath);
};
        
#endif
