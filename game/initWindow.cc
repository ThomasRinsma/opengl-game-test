#include "game.ih"

string const windowTitle = "Test";

void Game::initWindow(size_t width, size_t height)
{
	WindowSettings settings;
	settings.DepthBits = 24;
	settings.StencilBits = 8;
	settings.AntialiasingLevel = 2;

	// Make the window, using Style::Close for fixed size
	d_win = new Window(VideoMode(width, height), windowTitle, Style::Close, settings);

	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Disable VSync
	d_win->UseVerticalSync(false);

	// We're done initializing
	d_initialized = true;
}