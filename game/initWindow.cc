#include "game.ih"

string const windowTitle = "Test";

void Game::initWindow(size_t width, size_t height)
{
	// Make the window, using Style::Close for fixed size
	d_win = new Window(VideoMode(width, height), windowTitle, Style::Close, WindowSettings(24, 8, 2));

	// Make Controller object
	d_controller = new Controller(d_win);

	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win->UseVerticalSync(false);

	// Hide mouse cursor
	d_win->ShowMouseCursor(false);

	// Reset cursor to center
	d_win->SetCursorPosition(width / 2, height / 2);

	// We're done initializing
	d_initialized = true;
}