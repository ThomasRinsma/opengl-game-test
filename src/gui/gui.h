#ifndef INCLUDED_GUI_
#define INCLUDED_GUI_

#include <unordered_map>
#include <string>
#include <SFML/Window.hpp> // for sf::Window
#include <glm/glm.hpp> // for glm::mat4
#include "../drawableentity/drawableentity.h"
#include "../player/player.h"

class GUI
{
	std::unordered_map<std::string, DrawableEntity *> d_screenElements;
	glm::mat4 d_viewMat;
	glm::mat4 d_projMat;

    // Store Player to retrieve info from?
    // TODO: is this necesairy?
    Player &d_player;

    public:
        GUI(sf::Window &win, Player &player);
        ~GUI();

        void add(std::string const &name, DrawableEntity *object);
        void update(float deltaTime);
        void draw();

        DrawableEntity *get(std::string const &name);
        //glm::mat4 &getProjMat() const;

    private:
};

//inline glm::mat4 &GUI::getProjMat() const
//{
//	return d_projMat;
//}
        
#endif
