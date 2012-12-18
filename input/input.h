#ifndef INCLUDED_INPUT_
#define INCLUDED_INPUT_

#include <SFML/Window.hpp> // for sf::Key::Code

class Input
{
	typedef sf::Key::Code KeyCode_t;

	// These contain the state of input
	bool d_moveForward;
	bool d_moveBack;
	bool d_moveLeft;
	bool d_moveRight;

	// These contain the key mappings
	KeyCode_t d_keyForward;
	KeyCode_t d_keyBack;
	KeyCode_t d_keyLeft;
	KeyCode_t d_keyRight;

	public:
		Input(KeyCode_t keyForward = KeyCode_t::W, KeyCode_t keyBack = KeyCode_t::S, 
			KeyCode_t keyLeft = KeyCode_t::A, KeyCode_t keyRight = KeyCode_t::D);

		// Setters
		void keyPressed(KeyCode_t keyCode);
		void keyReleased(KeyCode_t keyCode);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;

	private:
		void setKeyState(KeyCode_t keyCode, bool state);
};


inline bool Input::moveForward() const
{
	return d_moveForward;
}

inline bool Input::moveBack() const
{
	return d_moveBack;
}

inline bool Input::moveLeft() const
{
	return d_moveLeft;
}

inline bool Input::moveRight() const
{
	return d_moveRight;
}
        
#endif
