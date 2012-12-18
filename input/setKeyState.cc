#include "input.ih"

void Input::setKeyState(KeyCode_t keyCode, bool state)
{
	if(keyCode == d_keyForward)
		d_moveForward = state;
	
	if(keyCode == d_keyBack)
		d_moveBack = state;

	if(keyCode == d_keyLeft)
		d_moveLeft = state;

	if(keyCode == d_keyRight)
		d_moveRight = state;
	
	// silently ignore other keypresses, TODO?
}