#ifndef INCLUDED_PORTAL_
#define INCLUDED_PORTAL_

#include <glm/glm.hpp>
#include "../object.h"
#include "../../shaderprogram/shaderprogram.h"


class Portal : public Object
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    public:
        Portal(ShaderProgram &shaderProgram);
        ~Portal();

    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
