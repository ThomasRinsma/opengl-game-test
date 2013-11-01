#ifndef INCLUDED_CONSOLE_
#define INCLUDED_CONSOLE_

#include <SFML/Window.hpp> // for sf::Window
#include <glm/glm.hpp> // for glm::vec3
#include <deque>
#include "../screenelement.h"
#include "../controller.h"
#include "../drawable/text.h"
#include "../resourcemanager.h"

class Console : public ScreenElement
{
	Controller &d_controller;
	sf::Window &d_win;

	// Text stuff
	Text d_consoleText;
	std::deque<std::string> d_lines;
	std::string d_inputLine;
	bool d_cursorState;
	float d_timeSinceBlink;

	GLuint d_vbo;
	GLuint d_vao;

	bool d_consoleDown;

	public:
		Console(Controller &controller, sf::Window &win);

		// Allow the outside to print stuff to the game console
		void printLine(std::string const &line);

	private:
		virtual void updateImpl(float deltaTime);
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);

		// helper functions for drawImpl()
		void drawBackground(glm::mat4 const &viewMat, glm::mat4 const &projMat);
		void drawText(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
		
#endif
