#include "game.ih"

string const windowTitle = "OpenGL Test";

Game::Game(size_t width, size_t height)
:
	d_winWidth(width),
	d_winHeight(height),
	d_win(sf::VideoMode(d_winWidth, d_winHeight), windowTitle, sf::Style::Close, sf::WindowSettings(24, 8, 2)),
	d_controller(d_win),
	d_player(d_controller)

{
	initWindow();
	initGraphics();
	initGame();
}