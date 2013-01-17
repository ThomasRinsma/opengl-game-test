#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public Drawable
{
	GLuint d_vao;
	GLuint d_vbo;
	GLuint d_tex;

    public:
        Cube(glm::vec3 position, ShaderProgram *shaderProgram, std::string const &texName);

    private:
    	virtual void drawImpl(glm::mat4 &viewMat, glm::mat4 &projMat);
};
        
#endif
