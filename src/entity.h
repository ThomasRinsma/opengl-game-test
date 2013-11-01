#ifndef INCLUDED_ENTITY_
#define INCLUDED_ENTITY_

#include <glm/glm.hpp> // for glm::vec3
#include <glm/gtc/quaternion.hpp>  // for glm::fquat

class Entity
{
	// These are for positionChanged()
	glm::vec3 d_prevPosition;
	bool d_positionChanged = true;

	protected:
		glm::mat4 d_modelMat;
		// TODO: acceleration?
		glm::vec3 d_velocity; // absolute
		glm::vec3 d_position;
		glm::vec3 d_scale; // relative
		glm::fquat d_orientation;

	public:
		Entity(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		virtual ~Entity();

		void update(float deltaTime);

		void setVelocity(glm::vec3 const &velocity);
		void setPosition(glm::vec3 const &position);
		void setScale(glm::vec3 const &scale);
		void addOrientation(glm::vec3 const &axes, float radAngle, bool worldSpace);
		void resetOrientation();

		bool positionChanged() const;

		glm::vec3 const &velocity() const;
		glm::vec3 const &position() const;
		glm::vec3 const &scale() const;
		glm::fquat const &orientation() const;


		glm::mat4 const modelMat() const;

	private:
		virtual void updateImpl(float deltaTime) = 0;
		void updateModelMat();
};

inline bool Entity::positionChanged() const
{
	return d_positionChanged;
}

inline glm::mat4 const Entity::modelMat() const
{
	return d_modelMat;
}

inline glm::vec3 const &Entity::velocity() const
{
	return d_velocity;
}

inline glm::vec3 const &Entity::position() const
{
	return d_position;
}

inline glm::vec3 const &Entity::scale() const
{
	return d_scale;
}

inline glm::fquat const &Entity::orientation() const
{
	return d_orientation;
}

inline void Entity::setVelocity(glm::vec3 const &velocity)
{
	d_velocity = velocity;
	updateModelMat();
}

inline void Entity::setPosition(glm::vec3 const &position)
{
	d_position = position;
	updateModelMat();
}

inline void Entity::setScale(glm::vec3 const &scale)
{
	d_scale = scale;
	updateModelMat();
}

inline void Entity::addOrientation(glm::vec3 const &axis, float radAngle, bool worldSpace)
{
	glm::vec3 axisNorm = glm::normalize(axis);
	
	axisNorm *= sin(radAngle / 2.0f);
	float scalar = cos(radAngle / 2.0f);
	
	glm::fquat offset(scalar, axisNorm);
	
	if(worldSpace)
		d_orientation = offset * d_orientation;
	else
		d_orientation = d_orientation * offset;
	
	d_orientation = glm::normalize(d_orientation);
	updateModelMat();
}

inline void Entity::resetOrientation()
{
	d_orientation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
	updateModelMat();
}
		
#endif
