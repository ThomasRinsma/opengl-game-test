#ifndef INCLUDED_GRID_
#define INCLUDED_GRID_


#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Grid : public Drawable
{
	GLuint d_vbo;
	GLuint d_vao;

    public:
        Grid(ShaderProgram *shaderProgram); // TODO: color
        ~Grid();

    private:
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
