#ifndef INCLUDED_COLLIDABLE_
#define INCLUDED_COLLIDABLE_

#include "entity.h"
#include <glm/glm.hpp> // for glm::vec3

class Collidable// : public Entity
{
	protected:
		Entity &d_parent;

	public:
		Collidable(Entity &parent);
		
		// collision with line
		bool isCollidingWith(glm::vec3 const &p1, glm::vec3 const &p2);

	private:
		virtual bool isCollidingWithImpl(glm::vec3 const &p1, glm::vec3 const &p2) = 0;
};
		
#endif
