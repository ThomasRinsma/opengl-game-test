#include "game.ih"

void Game::initGame()
{
	Cube* cube = new Cube(glm::vec3(0.0f), d_shaderProgram);

	d_drawables.push_back(cube);
}