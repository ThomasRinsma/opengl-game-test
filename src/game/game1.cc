#include "game.ih"

string const windowTitle = "OpenGL Test";

Game::Game()
:
	d_winWidth(sf::VideoMode::GetMode(0).Width),
	d_winHeight(sf::VideoMode::GetMode(0).Height),
	d_win(sf::VideoMode(d_winWidth, d_winHeight), windowTitle, sf::Style::Fullscreen, sf::WindowSettings(24, 8, 2)),
	d_controller(d_win),
	d_player(d_controller)

{
	initWindow();
	initGraphics();
	initGame();
}