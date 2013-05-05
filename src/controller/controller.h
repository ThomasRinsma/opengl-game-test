#ifndef INCLUDED_CONTROLLER_
#define INCLUDED_CONTROLLER_

#include <SFML/Window.hpp> // for sf::Key::Code and sf::Input
#include <glm/glm.hpp> // for glm::vec2

class Controller
{
	typedef sf::Keyboard::Key Key_t;

	sf::Window &d_win;

	bool d_enabled = true;

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
	bool d_closedWindow = false;
	bool d_lostFocus = false;
	bool d_gainedFocus = false;
	bool d_exitPressed = false;
	bool d_mouseLeftPressed = false;
	bool d_mouseRightPressed = false;
	bool d_mouseMiddlePressed = false;
	int  d_mouseWheelDelta = 0;


	public:
		Controller(sf::Window &win, Key_t keyForward = Key_t::W, Key_t keyBack = Key_t::S, 
			Key_t keyLeft = Key_t::A, Key_t keyRight = Key_t::D,
			Key_t keyUp = Key_t::Space, Key_t keyDown = Key_t::LControl,
			Key_t keyToggleConsole = Key_t::F12, Key_t keyToggleVsync = Key_t::F1,
			Key_t keyExit = Key_t::Escape);

		void enable();
		void disable();

		void update(float deltaTime);
		void processEvent(sf::Event &event);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;
		bool moveUp() const;
		bool moveDown() const;

		bool toggleConsole();
		bool toggleVsync();

		bool exit();

		bool closedWindow();
		bool lostFocus();
		bool gainedFocus();
		bool mouseLeft();
		bool mouseRight();
		bool mouseMiddle();
		int  mouseWheelDelta();


		glm::vec2 mouseOffset();
};

inline void Controller::enable()
{
	d_enabled = true;
}

inline void Controller::disable()
{
	d_enabled = false;
}


inline bool Controller::moveForward() const
{
	return d_enabled and d_keysPressed[d_keyForward];
}

inline bool Controller::moveBack() const
{
	return d_enabled and d_keysPressed[d_keyBack];
}

inline bool Controller::moveLeft() const
{
	return d_enabled and d_keysPressed[d_keyLeft];
}

inline bool Controller::moveRight() const
{
	return d_enabled and d_keysPressed[d_keyRight];
}

inline bool Controller::moveUp() const
{
	return d_enabled and d_keysPressed[d_keyUp];
}

inline bool Controller::moveDown() const
{
	return d_enabled and d_keysPressed[d_keyDown];
}

inline bool Controller::toggleConsole()
{
	// Don't listen to d_enabled, this allows us
	// to bring the console back up
	if (d_keysPressed[d_keyToggleConsole])
	{
		d_keysPressed[d_keyToggleConsole] = false;
		return true;
	}

	return false;
}

inline bool Controller::toggleVsync()
{
	if (d_keysPressed[d_keyToggleVsync])
	{
		d_keysPressed[d_keyToggleVsync] = false;
		return true;
	}

	return false;
}
  
inline bool Controller::exit()
{
	// Don't listen to d_enabled, this allows us
	// to exit the game while the console is open
	if (d_exitPressed)
	{
		d_exitPressed = false;
		return true;
	}

	return false;
}

inline bool Controller::closedWindow()
{
	if (d_closedWindow)
	{
		d_closedWindow = false;
		return true;
	}

	return false;
}

inline bool Controller::lostFocus()
{
	if (d_lostFocus)
	{
		d_lostFocus = false;
		return true;
	}

	return false;
}

inline bool Controller::gainedFocus()
{
	if (d_gainedFocus)
	{
		d_gainedFocus = false;
		return true;
	}

	return false;
}

inline bool Controller::mouseLeft()
{
	if (d_mouseLeftPressed)
	{
		d_mouseLeftPressed = false;
		return true;
	}

	return false;
}

inline bool Controller::mouseMiddle()
{
	if (d_mouseMiddlePressed)
	{
		d_mouseMiddlePressed = false;
		return true;
	}

	return false;
}


inline bool Controller::mouseRight()
{
	if (d_mouseRightPressed)
	{
		d_mouseRightPressed = false;
		return true;
	}

	return false;
}

inline int Controller::mouseWheelDelta()
{
	int m = d_mouseWheelDelta;
	d_mouseWheelDelta = 0;
	return m;
}

#endif
