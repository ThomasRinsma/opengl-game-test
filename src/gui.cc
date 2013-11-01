#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include "gui.h"

using namespace std;

GUI::GUI(sf::Window &win)
:
	d_viewMat(glm::mat4(1.0f)),
	d_projMat(glm::ortho(0.0f, (float)win.getSize().x, 0.0f, (float)win.getSize().y, -1.0f, 1.0f))
{}

void GUI::update(float deltaTime)
{
	for (auto &pair : d_screenElements)
		pair.second->update(deltaTime);
}

void GUI::add(string const &name, ScreenElement* element)
{
	d_screenElements[name] = unique_ptr<ScreenElement>(element);
}

// normal version
ScreenElement &GUI::get(std::string const &name)
{
	return *d_screenElements.at(name);
}

void GUI::draw()
{
	glDisable(GL_DEPTH_TEST);
	
	for (auto &pair : d_screenElements)
		pair.second->draw(d_viewMat, d_projMat);
}