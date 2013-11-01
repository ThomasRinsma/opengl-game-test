#ifndef INCLUDED_COLLIDABLEPLANE_
#define INCLUDED_COLLIDABLEPLANE_

#include "../collidable.h"
#include <glm/glm.hpp> // for glm::vec3

class CollidablePlane : public Collidable
{
	glm::vec3 d_p1, d_p2, d_p3, d_p4;

	public:
		CollidablePlane(Entity &parent, glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3, glm::vec3 const &p4);

	private:
		bool isCollidingWithImpl(glm::vec3 const &p1, glm::vec3 const &p2);
};
		
#endif
