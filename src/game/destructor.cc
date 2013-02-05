#include "game.ih"

Game::~Game()
{
	d_win.Close();

	for (ShaderProgram *sp : d_shaderPrograms)
		delete sp;
}