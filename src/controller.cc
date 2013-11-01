#include "controller.h"
#include <algorithm>
#include <iostream>

using namespace std;

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

void Controller::update(float deltaTime)
{
	if (not d_enabled)
		return;

	// Loop through all pending events
	sf::Event event;
	while (d_win.pollEvent(event))
	{
		processEvent(event);
	}
}

glm::vec2 Controller::mouseOffset()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(d_win);
	sf::Vector2i winCenter(d_win.getSize().x / 2, d_win.getSize().y / 2);

	sf::Mouse::setPosition(winCenter, d_win);

	if (d_enabled)
		return glm::vec2(mousePos.x - winCenter.x, mousePos.y - winCenter.y);
	else
		return glm::vec2(0.0f, 0.0f);
}

void Controller::processEvent(sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::Closed:
			d_closedWindow = true;
			break;

		case sf::Event::LostFocus:
			d_lostFocus = true;
			break;

		case sf::Event::GainedFocus:
			d_gainedFocus = true;
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == d_keyExit)
				d_exitPressed = true;
			else
				d_keysPressed[event.key.code] = true;
			break;

		case sf::Event::KeyReleased:
			d_keysPressed[event.key.code] = false;
			break;

		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Button::Left:
					d_mouseLeftPressed = true;
					break;

				case sf::Mouse::Button::Right:
					d_mouseRightPressed = true;
					break;

				case sf::Mouse::Button::Middle:
					d_mouseMiddlePressed = true;
					break;

				default:
					break;
			}
			break;

		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Button::Left:
					d_mouseLeftPressed = false;
					break;

				case sf::Mouse::Button::Right:
					d_mouseRightPressed = false;
					break;

				case sf::Mouse::Button::Middle:
					d_mouseMiddlePressed = false;
					break;

				default:
					break;
			}
			break;

		case sf::Event::MouseWheelMoved:
			d_mouseWheelDelta = event.mouseWheel.delta;
			break;

		default:
			break;
	}
}



