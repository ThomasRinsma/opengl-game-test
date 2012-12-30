#include "game.ih"

Game::~Game()
{
	delete d_controller;
	delete d_win;

	for (ShaderProgram* sp : d_shaderPrograms)
		delete sp;

	for (Drawable* drawable : d_drawables)
		delete drawable;

	// TODO: clean up opengl stuff
}