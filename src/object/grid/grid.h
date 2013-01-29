#ifndef INCLUDED_GRID_
#define INCLUDED_GRID_


#include <glm/glm.hpp>
#include "../object.h"
#include "../../shaderprogram/shaderprogram.h"


class Grid : public Object
{
	GLuint d_vbo;
	GLuint d_vao;

    public:
        Grid(ShaderProgram &shaderProgram); // TODO: color
        ~Grid();

    private:
    	virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &modelMat, glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
