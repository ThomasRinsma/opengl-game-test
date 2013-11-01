#include "collidable.h"

using namespace std;

Collidable::Collidable(Entity &parent)
:
	d_parent(parent)
{}

bool Collidable::isCollidingWith(glm::vec3 const &p1, glm::vec3 const &p2)
{
	return isCollidingWithImpl(p1, p2);
}