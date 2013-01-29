#include "game.ih"

void Game::initGame()
{
	Grid* grid = new Grid(*d_shaderPrograms[0]);
	Model* room = new Model(*d_shaderPrograms[1], "wall", "inverted_cube");
	Model* sphere = new Model(*d_shaderPrograms[1], "earth", "sphere");
	Cube* cube1 = new Cube(*d_shaderPrograms[1], "crate");
	Cube* cube2 = new Cube(*d_shaderPrograms[1], "crate");

	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized

	sphere->setPosition(glm::vec3(0.0f, 4.0f, -3.0f));

	cube1->setPosition(glm::vec3(2.0f, 1.5f, 2.0f));
	cube2->setPosition(glm::vec3(-2.0f, 1.5f, 2.0f));


	d_fpsText = new Text(*d_shaderPrograms[2], "");
	d_fpsText->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	d_objects.push_back(grid);
	d_objects.push_back(room);
	d_objects.push_back(cube1);
	d_objects.push_back(cube2);
	d_objects.push_back(sphere);
	d_objects.push_back(d_fpsText);


	d_player.setPosition(glm::vec3(0.0f, 4.0f, 5.0f));
}