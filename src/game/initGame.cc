#include "game.ih"

void Game::initGame()
{
	Grid* grid = new Grid(d_shaderPrograms[0]);

	Model* room = new Model(d_shaderPrograms[1], "wall", "inverted_cube");
	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized

	Model* sphere = new Model(d_shaderPrograms[1], "earth", "sphere");
	sphere->setPosition(glm::vec3(0.0f, 4.0f, 3.0f));

	Cube* cube1 = new Cube(d_shaderPrograms[1], "crate");
	cube1->setPosition(glm::vec3(2.0f, 1.5f, -2.0f));

	Cube* cube2 = new Cube(d_shaderPrograms[1], "crate");
	cube2->setPosition(glm::vec3(-2.0f, 1.5f, -2.0f));

	d_drawables.push_back(grid);
	d_drawables.push_back(room);
	d_drawables.push_back(cube1);
	d_drawables.push_back(cube2);
	d_drawables.push_back(sphere);


	d_player.setPosition(glm::vec3(0.0f, 4.0f, -5.0f));
}