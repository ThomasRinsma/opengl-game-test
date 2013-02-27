#include "gui.ih"

GUI::~GUI()
{
	for (pair<string, DrawableEntity *> pair : d_screenElements)
		delete pair.second;
}