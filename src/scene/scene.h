#ifndef INCLUDED_SCENE_
#define INCLUDED_SCENE_

#include <vector>
#include <glm/glm.hpp> // for glm::mat4
#include "../player/player.h"
#include "../drawableentity/drawableentity.h"
#include "../drawableentity/portal/portal.h"
#include "../light/light.h"

class Scene
{
    Player &d_player;

	std::vector<DrawableEntity *> d_drawableEntities;
	std::vector<Portal *> d_portals;
    std::vector<Light *> d_lights;

    static constexpr const size_t s_lightsPerObject = 8;
    static constexpr const float s_teleportThreshold = 0.3f;

    public:
        Scene(Player &player);
        ~Scene();

        void add(DrawableEntity *object);	// general
        void add(Portal *portal);		// specialized
        void add(Light *light);

        void update(float deltaTime);
        void draw();

    private:
        void drawRecursivePortals(glm::mat4 const &viewMat, glm::mat4 const &projMat, size_t recursionLevel);
    	void drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat);
        void updateLightData(DrawableEntity *drawableEntity);
        void handleCollisions();
};
        
#endif