#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public Drawable
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    public:
        Cube(ShaderProgram *shaderProgram, std::string const &texName);
        ~Cube();

    private:
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
