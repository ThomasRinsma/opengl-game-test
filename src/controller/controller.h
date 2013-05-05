#ifndef INCLUDED_CONTROLLER_
#define INCLUDED_CONTROLLER_

#include <SFML/Window.hpp> // for sf::Key::Code and sf::Input
#include <glm/glm.hpp> // for glm::vec2

class Controller
{
	typedef sf::Keyboard::Key Key_t;

	sf::Window &d_win;

	// These contain the key mappings
	Key_t d_keyForward;
	Key_t d_keyBack;
	Key_t d_keyLeft;
	Key_t d_keyRight;
	Key_t d_keyUp;
	Key_t d_keyDown;
	Key_t d_keyConsole;

	public:
		Controller(sf::Window &win, Key_t keyForward = Key_t::W, Key_t keyBack = Key_t::S, 
			Key_t keyLeft = Key_t::A, Key_t keyRight = Key_t::D,
			Key_t keyUp = Key_t::Space, Key_t keyDown = Key_t::LControl,
			Key_t keyConsole = Key_t::F12);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;
		bool moveUp() const;
		bool moveDown() const;
		bool toggleConsole() const;

		glm::vec2 mouseOffset();
};


inline bool Controller::moveForward() const
{
	return sf::Keyboard::isKeyPressed(d_keyForward);
}

inline bool Controller::moveBack() const
{
	return sf::Keyboard::isKeyPressed(d_keyBack);
}

inline bool Controller::moveLeft() const
{
	return sf::Keyboard::isKeyPressed(d_keyLeft);
}

inline bool Controller::moveRight() const
{
	return sf::Keyboard::isKeyPressed(d_keyRight);
}

inline bool Controller::moveUp() const
{
	return sf::Keyboard::isKeyPressed(d_keyUp);
}

inline bool Controller::moveDown() const
{
	return sf::Keyboard::isKeyPressed(d_keyDown);
}

inline bool Controller::toggleConsole() const
{
	return sf::Keyboard::isKeyPressed(d_keyConsole);
}
        
#endif
