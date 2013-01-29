#include "entity.ih"

void Entity::update(float deltaTime)
{
	updateImpl(deltaTime);
	modelMatUpdated(); // TODO: not always
}