#include "controller.ih"

Controller::Controller(Input const *input, KeyCode_t keyForward, KeyCode_t keyBack, KeyCode_t keyLeft, KeyCode_t keyRight)
:
	d_input(input),
	d_keyForward(keyForward),
	d_keyBack(keyBack),
	d_keyLeft(keyLeft),
	d_keyRight(keyRight)
{}