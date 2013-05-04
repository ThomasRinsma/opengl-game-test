#include "gui.ih"

void GUI::add(string const &name, ScreenElement* element)
{
	d_screenElements[name] = unique_ptr<ScreenElement>(element);
}