#ifndef INCLUDED_PORTAL_
#define INCLUDED_PORTAL_

#include <glm/glm.hpp>
#include "../drawableentity.h"
#include "../../shaderprogram/shaderprogram.h"
#include "../../entity/entity.h"


class Portal : public DrawableEntity
{
	Entity *d_destination;

	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    public:
        Portal(ShaderProgram &shaderProgram, Entity *destination = nullptr);
        ~Portal();

        Entity *destination() const;
        void setDestination(Entity *destination);

        glm::mat4 const clippedProjMat(glm::mat4 const &viewMat, glm::mat4 const &projMat) const;

    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline Entity *Portal::destination() const
{
	return d_destination;
}

inline void Portal::setDestination(Entity *destination)
{
	d_destination = destination;
}
        
#endif