#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../object.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public Object
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    public:
        Cube(ShaderProgram &shaderProgram, std::string const &texName);
        ~Cube();


    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &modelMat, glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
