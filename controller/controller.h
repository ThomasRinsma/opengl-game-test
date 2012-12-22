#ifndef INCLUDED_CONTROLLER_
#define INCLUDED_CONTROLLER_

#include <SFML/Window.hpp> // for sf::Key::Code and sf::Input
#include <glm/glm.hpp> // for glm::vec2

class Controller
{
	typedef sf::Key::Code KeyCode_t;

	sf::Input const *d_input;

	// These contain the key mappings
	KeyCode_t d_keyForward;
	KeyCode_t d_keyBack;
	KeyCode_t d_keyLeft;
	KeyCode_t d_keyRight;

	public:
		Controller(sf::Input const *input, KeyCode_t keyForward = KeyCode_t::W, KeyCode_t keyBack = KeyCode_t::S, 
			KeyCode_t keyLeft = KeyCode_t::A, KeyCode_t keyRight = KeyCode_t::D);

		// Getters
		bool moveForward() const;
		bool moveBack() const;
		bool moveLeft() const;
		bool moveRight() const;

		glm::vec2 mousePosition() const;
};


inline bool Controller::moveForward() const
{
	return d_input->IsKeyDown(d_keyForward);
}

inline bool Controller::moveBack() const
{
	return d_input->IsKeyDown(d_keyBack);
}

inline bool Controller::moveLeft() const
{
	return d_input->IsKeyDown(d_keyLeft);
}

inline bool Controller::moveRight() const
{
	return d_input->IsKeyDown(d_keyRight);
}
        
#endif
