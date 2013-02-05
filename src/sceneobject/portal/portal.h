#ifndef INCLUDED_PORTAL_
#define INCLUDED_PORTAL_

#include <glm/glm.hpp>
#include "../sceneobject.h"
#include "../../shaderprogram/shaderprogram.h"
#include "../../entity/entity.h"


class Portal : public SceneObject
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
