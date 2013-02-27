#include "gui.ih"

void GUI::draw()
{
	for (pair<string, DrawableEntity *> pair : d_screenElements)
		pair.second->draw(d_viewMat, d_projMat);
}