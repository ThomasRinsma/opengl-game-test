#include "controller.ih"

Controller::Controller(sf::Window &win, Key_t keyForward, Key_t keyBack, Key_t keyLeft, Key_t keyRight,
	Key_t keyUp, Key_t keyDown, Key_t keyToggleConsole, Key_t keyToggleVsync, Key_t keyExit)
:
	d_win(win),
	d_keyForward(keyForward),
	d_keyBack(keyBack),
	d_keyLeft(keyLeft),
	d_keyRight(keyRight),
	d_keyUp(keyUp),
	d_keyDown(keyDown),
	d_keyToggleConsole(keyToggleConsole),
	d_keyToggleVsync(keyToggleVsync),
	d_keyExit(keyExit)
{
	fill(begin(d_keysPressed), end(d_keysPressed), false);
}