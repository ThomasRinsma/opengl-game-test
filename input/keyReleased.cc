#include "input.ih"

void Input::keyReleased(sf::Key::Code keyCode)
{
	setKeyState(keyCode, false);
}
