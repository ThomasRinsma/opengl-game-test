#include "gui.ih"

void GUI::add(std::string const &name, DrawableEntity *object)
{
	d_screenElements.emplace(name, object);
}