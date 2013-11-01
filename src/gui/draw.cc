#include "gui.ih"

void GUI::draw()
{
	glDisable(GL_DEPTH_TEST);
	
	for (auto &pair : d_screenElements)
		pair.second->draw(d_viewMat, d_projMat);
}