#ifndef INCLUDED_CUBE_
#define INCLUDED_CUBE_

#include <glm/glm.hpp>
#include "../drawableentity.h"
#include "../../texture/texture.h"
#include "../../shaderprogram/shaderprogram.h"


class Cube : public DrawableEntity
{
	GLuint d_vbo;
	GLuint d_vao;

	Texture &d_texture;

    public:
        Cube(std::string const &texName);
        ~Cube();

        virtual bool needsLighting() const;


    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline bool Cube::needsLighting() const
{
	return true;
}
        
#endif
