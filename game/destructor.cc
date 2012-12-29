#include "game.ih"

Game::~Game()
{
	delete d_controller;
	delete d_win;
	delete d_shaderProgram;

	for (Drawable* drawable : d_drawables)
		delete drawable;

	// TODO: clean up opengl stuff
}