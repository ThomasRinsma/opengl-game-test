#include "controller.ih"

vec2 Controller::mousePosition() const
{
	vec2 mouseDelta(d_input->GetMouseX(), d_input->GetMouseY());

	return mouseDelta;
}