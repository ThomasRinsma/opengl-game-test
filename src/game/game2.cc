#include "game.ih"

string const windowTitle = "OpenGL Test";

Game::Game(size_t width, size_t height)
:
	d_fullscreen(false),
	d_win(sf::VideoMode(width, height), windowTitle, sf::Style::Close, sf::ContextSettings(24, 8, 0, 3, 2)),
	d_controller(d_win),
	d_player(d_controller)
{
	initWindow();
	initGraphics();
	initGame();
}