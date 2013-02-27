#include "gui.ih"

DrawableEntity *GUI::get(std::string const &name)
{
	return d_screenElements.at(name);
}