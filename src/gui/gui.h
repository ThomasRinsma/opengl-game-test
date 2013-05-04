#ifndef INCLUDED_GUI_
#define INCLUDED_GUI_

#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Window.hpp> // for sf::Window
#include <glm/glm.hpp> // for glm::mat4
#include "../screenelement/screenelement.h"

class GUI
{
	std::unordered_map<std::string, std::unique_ptr<ScreenElement>> d_screenElements;
	glm::mat4 d_viewMat;
	glm::mat4 d_projMat;

    public:
        GUI(sf::Window &win);

        void add(std::string const &name, ScreenElement* element);
        void update(float deltaTime);
        void draw();

        ScreenElement &get(std::string const &name);

        template <typename T>
        T &get(std::string const &name);

    private:
};

// templated version
template <typename T>
T &GUI::get(std::string const &name)
{
    return dynamic_cast<T &>(*d_screenElements.at(name));
}  
#endif
