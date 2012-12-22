#include "game.ih"

Game::~Game()
{
	delete d_controller;
	delete d_win;

	// TODO: clean up opengl stuff
}