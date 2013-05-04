#include "gui.ih"

// normal version
ScreenElement &GUI::get(std::string const &name)
{
	return *d_screenElements.at(name);
}