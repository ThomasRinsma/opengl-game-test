#include "game.ih"

Game::~Game()
{
	d_win.Close();

	for (ShaderProgram *sp : d_shaderPrograms)
		delete sp;

	for (Object *object : d_objects)
		delete object;
}