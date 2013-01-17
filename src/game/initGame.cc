#include "game.ih"

void Game::initGame()
{
	Grid* grid = new Grid(glm::vec3(0.0f), d_shaderPrograms[0]);

	Cube* cube1 = new Cube(glm::vec3(0.0f), d_shaderPrograms[1], "crate");
	cube1->setPosition(glm::vec3(2.0f, 0.5f, 0.0f));

	Cube* cube2 = new Cube(glm::vec3(0.0f), d_shaderPrograms[1], "crate");
	cube2->setPosition(glm::vec3(-2.0f, 0.5f, 0.0f));

	Model* sphere = new Model(glm::vec3(0.0f), d_shaderPrograms[1], "earth", "sphere");
	sphere->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));


	d_drawables.push_back(grid);
	d_drawables.push_back(cube1);
	d_drawables.push_back(cube2);
	d_drawables.push_back(sphere);
}