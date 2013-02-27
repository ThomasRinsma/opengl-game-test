#include "controller.ih"

Controller::Controller(sf::Window &win, Key_t keyForward, Key_t keyBack, Key_t keyLeft, Key_t keyRight,
	Key_t keyUp, Key_t keyDown)
:
	d_win(win),
	d_keyForward(keyForward),
	d_keyBack(keyBack),
	d_keyLeft(keyLeft),
	d_keyRight(keyRight),
	d_keyUp(keyUp),
	d_keyDown(keyDown)
{
	// Hide mouse cursor
	d_win.setMouseCursorVisible(false);

	// Reset cursor to center
	sf::Vector2i winCenter(d_win.getSize().x / 2, d_win.getSize().y / 2);
	sf::Mouse::setPosition(winCenter, d_win);
}