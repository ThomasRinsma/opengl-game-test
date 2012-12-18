#include "input.ih"

void Input::keyPressed(sf::Key::Code keyCode)
{
	setKeyState(keyCode, true);
}
