#include "gui.ih"

GUI::GUI(sf::Window &win)
:
	d_viewMat(glm::mat4(1.0f)),
	d_projMat(glm::ortho(0.0f, (float)win.getSize().x, 0.0f, (float)win.getSize().y, -1.0f, 1.0f))
{}
