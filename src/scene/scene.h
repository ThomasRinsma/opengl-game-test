#ifndef INCLUDED_SCENE_
#define INCLUDED_SCENE_

#include <vector>
#include <glm/glm.hpp> // for glm::mat4
#include "../player/player.h"
#include "../drawableentity/drawableentity.h"
#include "../drawableentity/portal/portal.h"

class Scene
{
	std::vector<DrawableEntity *> d_drawableEntities;
	std::vector<Portal *> d_portals;

    public:
        Scene();
        ~Scene();

        void add(DrawableEntity *object);	// general
        void add(Portal *portal);		// specialized

        void update(float deltaTime);
        void draw(Player const &player);

    private:
    	void drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif