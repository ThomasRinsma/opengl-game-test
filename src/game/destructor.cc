#include "game.ih"

Game::~Game()
{
	d_win.close();

	for (ShaderProgram *sp : d_shaderPrograms)
		delete sp;
}