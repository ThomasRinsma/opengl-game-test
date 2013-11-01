#include "controller.ih"
#include <iostream>

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