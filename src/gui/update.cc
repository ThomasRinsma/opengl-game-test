#include "gui.ih"

void GUI::update(float deltaTime)
{
	for (pair<string, DrawableEntity *> pair : d_screenElements)
		pair.second->update(deltaTime);
}