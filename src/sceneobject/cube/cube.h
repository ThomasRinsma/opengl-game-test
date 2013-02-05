#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../sceneobject.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public SceneObject
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    public:
        Cube(ShaderProgram &shaderProgram, std::string const &texName);
        ~Cube();


    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
