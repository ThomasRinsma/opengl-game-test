#include "game.ih"

string const windowTitle = "OpenGL Test";

Game::Game()
:
	d_fullscreen(true),
	d_win(sf::VideoMode::getDesktopMode(), windowTitle, sf::Style::Fullscreen, sf::ContextSettings(24, 8, 0, 3, 2)),
	d_controller(d_win),
	d_player(d_controller),
	d_gui(d_win, d_player)
{
	initWindow();
	initGraphics();
	initGame();
}