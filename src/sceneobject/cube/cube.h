#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../sceneobject.h"
#include "../../texture/texture.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public SceneObject
{
	GLuint d_vbo;
	GLuint d_vao;

	Texture &d_texture;

    public:
        Cube(std::string const &texName);
        ~Cube();

        bool needsLighting() const;


    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline bool Cube::needsLighting() const
{
	return true;
}
        
#endif
