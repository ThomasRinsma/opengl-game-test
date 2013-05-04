#ifndef INCLUDED_SCENE_
#define INCLUDED_SCENE_

#include <memory>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp> // for glm::mat4
#include "../sceneobject/sceneobject.h"
#include "../sceneobject/portal/portal.h"
#include "../player/player.h"
#include "../light/light.h"

class Scene
{
    Player &d_player;

    std::unordered_map<std::string, std::unique_ptr<SceneObject>> d_sceneObjects;
    std::unordered_map<std::string, std::unique_ptr<Portal>> d_portals;
    std::unordered_map<std::string, std::unique_ptr<Light>> d_lights;

    static constexpr const size_t s_lightsPerObject = 8;
    static constexpr const float s_teleportThreshold = 0.3f;

    public:
        Scene(Player &player);

        void add(std::string const name, SceneObject *object);	// general
        void add(std::string const name, Portal *portal);		// specialized
        void add(std::string const name, Light *light);     // specialized

        void update(float deltaTime);
        void draw();

    private:
        void drawRecursivePortals(glm::mat4 const &viewMat, glm::mat4 const &projMat, size_t maxRecursionLevel, size_t recursionLevel = 0);
    	void drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat);
        void updateLightData(SceneObject &sceneObject);
        void handleCollisions();
};
        
#endif