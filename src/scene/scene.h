#ifndef INCLUDED_SCENE_
#define INCLUDED_SCENE_

#include <vector>
#include <glm/glm.hpp> // for glm::mat4
#include "../player/player.h"
#include "../sceneobject/sceneobject.h"
#include "../sceneobject/portal/portal.h"

class Scene
{
	std::vector<SceneObject *> d_sceneObjects;
	std::vector<Portal *> d_portals;

    public:
        Scene();
        ~Scene();

        void add(SceneObject *object);	// general
        void add(Portal *portal);		// specialized

        void update(float deltaTime);
        void draw(Player const &player);

    private:
    	void drawSceneObjects(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif