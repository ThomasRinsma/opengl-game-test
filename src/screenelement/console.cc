#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "console.h"

using namespace std;

// 1 = opaque, 0 = transparent
float consoleTrans = 0.75f;

Console::Console(Controller &controller, sf::Window &win)
:
	ScreenElement(ResourceManager::instance().shaderProgram("simpleColor")),
	d_controller(controller),
	d_win(win),
	d_lines(14, ""),
	d_inputLine(""),
	d_cursorState(false),
	d_timeSinceBlink(0.0f),
	d_consoleDown(false)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Console background vertices:   X, Y, Z,  R, G, B
	float vertices[] = {
		0.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		0.0f, 1.0f,  0.0f,    0.0f, 0.0f, 0.0f,
		0.0f, 0.0f,  0.0f,    0.0f, 0.0f, 0.0f,
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram.attribute("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}

void Console::updateImpl(float deltaTime)
{
	// If the toggle button was pressed since the last update
	if (d_controller.toggleConsole())
	{
		d_consoleDown = not d_consoleDown;

		// Disable (most of) the controller's input handling
		// while the console is visible
		if (d_consoleDown)
			d_controller.disable();
		else
			d_controller.enable();
	}

	// The console is down (visible)
	if (d_consoleDown)
	{
		// Capture key presses
		sf::Event event;
		while (d_win.pollEvent(event))
		{
			// If it's ascii and not ESC
			if (event.type == sf::Event::TextEntered and event.text.unicode < 128 and event.text.unicode != 27)
			{
				char c = static_cast<char>(event.text.unicode);

				// Backspace pressed and string not empty: remove last character
				if (c == 8 and d_inputLine.size() > 0)
					d_inputLine.pop_back(); // yay c++11

				// Readable character, append it
				if (c >= ' ' and c <= '~')
					d_inputLine.push_back(c);

				// Enter was pressed
				if ((c == '\n' || c == '\r') and d_inputLine.size() > 0)
				{
					d_lines.push_front("^7You entered: " + d_inputLine);

					d_inputLine.clear();
				}
			}
			else if(event.type == sf::Event::MouseWheelMoved)
			{
				// TODO: possible scroll the console history?
				// for now just silently ignore
			}
			else
				d_controller.processEvent(event);
		}

		// Generate new text, 14 lines of history plus the input line
		string totalText;

		// Concatenate all history lines in the queue
		for (int idx = 13; idx >= 0; --idx)
			totalText += d_lines[idx] + "\n";

		// Append the current input line
		totalText += "^1> ^7" + d_inputLine;

		// Blink time!
		if (d_timeSinceBlink > 0.5f)
		{
			d_cursorState = not d_cursorState;
			d_timeSinceBlink = 0.0f;
		}

		// Draw white cursor every other 0.5 seconds
		if (d_cursorState)
			totalText += "^7_";

		// Update counter, # of seconds since last blink
		d_timeSinceBlink += deltaTime;

		// Submit string to Text object
		d_consoleText.setText(totalText);
	}
}

void Console::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	if (d_consoleDown)
	{
		// Draw console background
		drawBackground(viewMat, projMat);

		// Draw console text
		drawText(viewMat, projMat);
	}
}

void Console::drawBackground(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * glm::translate(d_modelMat, glm::vec3(0.0f, -1.0f, 0.0f));
	glUniform1f(d_shaderProgram.uniform("trans"), consoleTrans);
	glUniformMatrix4fv(d_shaderProgram.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw console background
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Console::drawText(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	glm::mat4 d_consoleTextModelMat = glm::scale(
		glm::translate(
			glm::mat4(1.0f), glm::vec3(d_position.x + 4.0f, d_position.y - 20.0f, 0.0f)
		),
		glm::vec3(16.0f, 16.0f, 1.0f)
	);

	
	d_consoleText.setModelMat(d_consoleTextModelMat);
	d_consoleText.draw(viewMat, projMat);
}

void Console::printLine(std::string const &line)
{
	// TODO: length checking maybe, and/or auto wrapping
	d_lines.push_front(line);
}

