#include "game.ih"

void Game::initGame()
{
	Grid* grid = new Grid(glm::vec3(0.0f), d_shaderPrograms[0]);
	Cube* cube = new Cube(glm::vec3(0.0f), d_shaderPrograms[1]);

	d_drawables.push_back(grid);
	d_drawables.push_back(cube);
}