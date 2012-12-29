#include "controller.ih"

vec2 Controller::mouseOffset()
{
	vec2 mouse(d_win->GetInput().GetMouseX(), d_win->GetInput().GetMouseY());
	vec2 center(d_win->GetWidth() / 2, d_win->GetHeight() / 2);

	d_win->SetCursorPosition(center.x, center.y);

	return mouse - center;
}