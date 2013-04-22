#include "gui.ih"

void GUI::add(string const &name, DrawableEntity* object)
{
	d_screenElements[name] = unique_ptr<DrawableEntity>(object);
}