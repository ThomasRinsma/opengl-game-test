#ifndef INCLUDED_PLAYER_
#define INCLUDED_PLAYER_

#include <glm/glm.hpp> // for glm::vec3 and glm::mat4
#include "../controller/controller.h"
#include "../entity/entity.h"

class Player : public Entity
{
    static constexpr float s_mouseSpeed = 0.001f * M_PI; // radians per pixel
    static constexpr float s_moveSpeed = 2.0f; // units per second

    Controller &d_controller;

    public:
        Player(Controller &controller);
        glm::mat4 const viewMatrix() const;

    private:
        void updateImpl(float deltaTime);
        void integratePosition(float deltaTime);
        void setRelativeVelocity(glm::vec3 const &velocity);
        void modelMatUpdated();
};

        
#endif
