#ifndef INCLUDED_CONTROLLER_
#define INCLUDED_CONTROLLER_

#include <SFML/Window.hpp> // for sf::Key::Code and sf::Input
#include <glm/glm.hpp> // for glm::vec2

class Controller
{
	typedef sf::Key::Code KeyCode_t;

	sf::Window *d_win;

	// These contain the key mappings
	KeyCode_t d_keyForward;
	KeyCode_t d_keyBack;
	KeyCode_t d_keyLeft;
	KeyCode_t d_keyRight;
	KeyCode_t d_keyUp;
	KeyCode_t d_keyDown;

	public:
		Controller(sf::Window *win, KeyCode_t keyForward = KeyCode_t::W, KeyCode_t keyBack = KeyCode_t::S, 
			KeyCode_t keyLeft = KeyCode_t::A, KeyCode_t keyRight = KeyCode_t::D,
			KeyCode_t keyUp = KeyCode_t::Space, KeyCode_t keyDown = KeyCode_t::LControl);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;
		bool moveUp() const;
		bool moveDown() const;

		glm::vec2 mouseOffset();
};


inline bool Controller::moveForward() const
{
	return d_win->GetInput().IsKeyDown(d_keyForward);
}

inline bool Controller::moveBack() const
{
	return d_win->GetInput().IsKeyDown(d_keyBack);
}

inline bool Controller::moveLeft() const
{
	return d_win->GetInput().IsKeyDown(d_keyLeft);
}

inline bool Controller::moveRight() const
{
	return d_win->GetInput().IsKeyDown(d_keyRight);
}

inline bool Controller::moveUp() const
{
	return d_win->GetInput().IsKeyDown(d_keyUp);
}

inline bool Controller::moveDown() const
{
	return d_win->GetInput().IsKeyDown(d_keyDown);
}
        
#endif
