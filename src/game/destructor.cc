#include "game.ih"

Game::~Game()
{
	for (ShaderProgram *sp : d_shaderPrograms)
		delete sp;
	
	d_win.close();
}