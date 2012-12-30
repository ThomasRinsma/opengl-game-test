#include "game.ih"

string const windowTitle = "Test";

void Game::initWindow(size_t width, size_t height)
{
	// Make the window, using Style::Close for fixed size
	d_win = new sf::Window(sf::VideoMode(width, height), windowTitle, sf::Style::Close, sf::WindowSettings(24, 8, 2));

	// Make Controller object
	d_controller = new Controller(d_win);

	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win->UseVerticalSync(false);

	// We're done initializing
	d_initialized = true;
}