#include "entity.ih"

void Entity::update(float deltaTime)
{
	updateImpl(deltaTime);
	updateModelMat(); // TODO: not always
}