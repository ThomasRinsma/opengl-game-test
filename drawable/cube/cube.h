#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public Drawable
{
    public:
        Cube(glm::vec3 position, ShaderProgram *shaderProgram);

    private:
    	virtual void drawImpl(glm::mat4 viewProjMat);
};
        
#endif
