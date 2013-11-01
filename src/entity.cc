#include "entity.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Entity::Entity(glm::vec3 position, glm::vec3 scale)
:
	d_velocity(0.0f),
	d_position(position),
	d_scale(scale),
	d_orientation(1.0f, 0.0f, 0.0f, 0.0f)
{
	updateModelMat();
}

Entity::~Entity()
{}

void Entity::update(float deltaTime)
{
	// Save previous position
	d_prevPosition = d_position;

	// Implemented by inheriting class
	updateImpl(deltaTime);

	// Update model matrix to reflect new pos/ori/scale
	updateModelMat();
 
	d_positionChanged = (d_position != d_prevPosition);
}

void Entity::updateModelMat()
{
	d_modelMat = glm::scale(glm::translate(glm::mat4(1.0f), d_position) * glm::mat4_cast(d_orientation), d_scale);
}