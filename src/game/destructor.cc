#include "game.ih"

Game::~Game()
{
	d_win.Close();

	for (ShaderProgram* sp : d_shaderPrograms)
		delete sp;

	for (Drawable* drawable : d_drawables)
		delete drawable;

	// TODO: clean up opengl stuff
}