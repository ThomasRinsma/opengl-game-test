#include "gui.ih"

void GUI::update(float deltaTime)
{
	for (auto &pair : d_screenElements)
		pair.second->update(deltaTime);
}