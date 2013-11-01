#include "collidableplane.h"

using namespace std;

CollidablePlane::CollidablePlane(Entity &parent, glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3, glm::vec3 const &p4)
:
	Collidable(parent),
	d_p1(p1),
	d_p2(p2),
	d_p3(p3),
	d_p4(p4)
{}

bool CollidablePlane::isCollidingWithImpl(glm::vec3 const &p1, glm::vec3 const &p2)
{
	// Use absolute position by adding parent Entity's position
	glm::vec3 p1Abs = d_parent.position() + d_p1;
	glm::vec3 p2Abs = d_parent.position() + d_p2;
	glm::vec3 p3Abs = d_parent.position() + d_p3;
	glm::vec3 p4Abs = d_parent.position() + d_p4;

	glm::vec3 centerPoint = (p1Abs + p2Abs + p3Abs + p4Abs) / 4.0f;
	glm::vec3 planeNormal = glm::normalize(glm::cross(p3Abs - p1Abs, p2Abs - p1Abs));

	float dot1 = glm::dot(p1 - centerPoint, planeNormal);
	float dot2 = glm::dot(p2 - centerPoint, planeNormal);

	// We're colliding if p1 and p2 are on different sides of the plane
	return ((dot1 >= 0.0f and dot2 < 0.0f) or (dot1 < 0.0f and dot2 >= 0.0f));
}