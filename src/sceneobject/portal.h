#ifndef INCLUDED_PORTAL_
#define INCLUDED_PORTAL_

#include <glm/glm.hpp>
#include "../sceneobject.h"
#include "../shaderprogram.h"
#include "../entity.h"


class Portal : public SceneObject
{
	GLuint d_vbo;
	GLuint d_vao;

	Entity *d_destination;
	
	public:
		Portal(Entity *destination = nullptr);
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
