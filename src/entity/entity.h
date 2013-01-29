#ifndef INCLUDED_ENTITY_
#define INCLUDED_ENTITY_

#include <glm/glm.hpp> // for glm::vec3

class Entity
{
    protected:
        // TODO: acceleration?
    	glm::vec3 d_velocity; // absolute
        glm::vec3 d_position;
        glm::vec3 d_rotation;
        glm::vec3 d_scale; // relative

    public:
    	Entity();
    	virtual ~Entity();

    	void update(float deltaTime);

        void setPosition(glm::vec3 const &position);
        void setVelocity(glm::vec3 const &velocity);
        void setRotation(glm::vec3 const &rotation);
        void setScale(glm::vec3 const &scale);

        glm::vec3 const &position() const;
        glm::vec3 const &velocity() const;
        glm::vec3 const &rotation() const;
        glm::vec3 const &scale() const;

        // also allow rotation by seperate components
        void setRoll(float roll);
	    void setPitch(float pitch);
	    void setYaw(float yaw);

        float roll() const;
        float pitch() const;
        float yaw() const;

        glm::mat4 const modelMat() const;

    private:
    	virtual void updateImpl(float deltaTime) = 0;
};

inline glm::vec3 const &Entity::position() const
{
    return d_position;
}

inline glm::vec3 const &Entity::velocity() const
{
    return d_velocity;
}

inline glm::vec3 const &Entity::rotation() const
{
    return d_rotation;
}

inline glm::vec3 const &Entity::scale() const
{
    return d_scale;
}


inline float Entity::roll() const
{
    return d_rotation.z;
}

inline float Entity::pitch() const
{
	return d_rotation.x;
}

inline float Entity::yaw() const
{
	return d_rotation.y;
}

inline void Entity::setPosition(glm::vec3 const &position)
{
    d_position = position;
}

inline void Entity::setVelocity(glm::vec3 const &velocity)
{
    d_velocity = velocity;
}

inline void Entity::setRotation(glm::vec3 const &rotation)
{
    d_rotation = rotation;
}

inline void Entity::setScale(glm::vec3 const &scale)
{
    d_scale = scale;
}

inline void Entity::setRoll(float roll)
{
    d_rotation.z = roll;
}

inline void Entity::setPitch(float pitch)
{
    d_rotation.x = pitch;
}

inline void Entity::setYaw(float yaw)
{
    d_rotation.y = yaw;
}
        
#endif
