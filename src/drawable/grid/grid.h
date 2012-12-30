#ifndef INCLUDED_GRID_
#define INCLUDED_GRID_


#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Grid : public Drawable
{
	GLuint d_vao;
	GLuint d_vbo;

    public:
        Grid(glm::vec3 position, ShaderProgram *shaderProgram);

    private:
    	virtual void drawImpl(glm::mat4 &viewProjMat);
};
        
#endif
