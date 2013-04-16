#ifndef INCLUDED_GUI_
#define INCLUDED_GUI_

#include <unordered_map>
#include <string>
#include <SFML/Window.hpp> // for sf::Window
#include <glm/glm.hpp> // for glm::mat4
#include "../drawableentity/drawableentity.h"

class GUI
{
	std::unordered_map<std::string, DrawableEntity *> d_screenElements;
	glm::mat4 d_viewMat;
	glm::mat4 d_projMat;

    public:
        GUI(sf::Window &win);
        ~GUI();

        void add(std::string const &name, DrawableEntity *object);
        void update(float deltaTime);
        void draw();

        DrawableEntity *get(std::string const &name);

    private:
};
        
#endif
