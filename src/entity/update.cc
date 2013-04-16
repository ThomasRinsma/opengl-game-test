#include "entity.ih"

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