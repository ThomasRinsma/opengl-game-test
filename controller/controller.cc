#include "controller.ih"

Controller::Controller(sf::Window *win, KeyCode_t keyForward, KeyCode_t keyBack, KeyCode_t keyLeft, KeyCode_t keyRight,
	KeyCode_t keyUp, KeyCode_t keyDown)
:
	d_win(win),
	d_keyForward(keyForward),
	d_keyBack(keyBack),
	d_keyLeft(keyLeft),
	d_keyRight(keyRight),
	d_keyUp(keyUp),
	d_keyDown(keyDown)
{}