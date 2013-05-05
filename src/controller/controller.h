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
	Key_t d_keyToggleConsole;
	Key_t d_keyToggleVsync;
	Key_t d_keyExit;

	// All keys that were pressed since last update
	bool d_keysPressed[Key_t::KeyCount];

	// Other flags and states
	public:
		bool closedWindow;
		bool lostFocus;
		bool gainedFocus;
		bool exitPressed;
		bool mouseLeftPressed;
		bool mouseRightPressed;
		bool mouseMiddlePressed;
		int  mouseWheelDelta;


	public:
		Controller(sf::Window &win, Key_t keyForward = Key_t::W, Key_t keyBack = Key_t::S, 
			Key_t keyLeft = Key_t::A, Key_t keyRight = Key_t::D,
			Key_t keyUp = Key_t::Space, Key_t keyDown = Key_t::LControl,
			Key_t keyToggleConsole = Key_t::F12, Key_t keyToggleVsync = Key_t::F1,
			Key_t keyExit = Key_t::Escape);

		void update(float deltaTime);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;
		bool moveUp() const;
		bool moveDown() const;

		bool toggleConsole() const;
		bool toggleVsync() const;

		bool exit() const;

		glm::vec2 mouseOffset();
};


inline bool Controller::moveForward() const
{
	return d_keysPressed[d_keyForward];
}

inline bool Controller::moveBack() const
{
	return d_keysPressed[d_keyBack];
}

inline bool Controller::moveLeft() const
{
	return d_keysPressed[d_keyLeft];
}

inline bool Controller::moveRight() const
{
	return d_keysPressed[d_keyRight];
}

inline bool Controller::moveUp() const
{
	return d_keysPressed[d_keyUp];
}

inline bool Controller::moveDown() const
{
	return d_keysPressed[d_keyDown];
}

inline bool Controller::toggleConsole() const
{
	return d_keysPressed[d_keyToggleConsole];
}

inline bool Controller::toggleVsync() const
{
	return d_keysPressed[d_keyToggleVsync];
}
  
inline bool Controller::exit() const
{
	return exitPressed;
}

#endif
