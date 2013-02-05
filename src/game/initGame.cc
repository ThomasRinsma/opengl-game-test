#include "game.ih"

void Game::initGame()
{
	Grid* grid = new Grid(*d_shaderPrograms[0]);
	Model* room = new Model(*d_shaderPrograms[1], "wall", "inverted_cube");
	Model* monkey = new Model(*d_shaderPrograms[1], "wall", "monkey");
	Cube* cube1 = new Cube(*d_shaderPrograms[1], "crate");
	Cube* cube2 = new Cube(*d_shaderPrograms[1], "crate");

	Portal *portal1 = new Portal(*d_shaderPrograms[0]);
	Portal *portal2 = new Portal(*d_shaderPrograms[0]);

	portal1->setDestination(portal2);
	portal2->setDestination(portal1);

	d_debugText = new Text2D(*d_shaderPrograms[2], glm::vec2(4.0f, d_winHeight - 20.0f), glm::vec2(2.0f), "");

	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized
	monkey->setPosition(glm::vec3(0.0f, 2.0f, -3.0f));
	cube1->setPosition(glm::vec3(2.0f, 1.5f, 3.0f));
	cube2->setPosition(glm::vec3(-2.0f, 1.5f, 3.0f));

	portal1->setPosition(glm::vec3(-2.0f, 1.5f, 0.0f));
	portal2->setPosition(glm::vec3( 2.0f, 1.5f, 0.0f));
	portal2->setYaw(-90.0f);


	d_scene.add(grid);
	d_scene.add(room);
	d_scene.add(cube1);
	d_scene.add(cube2);
	d_scene.add(monkey);
	d_scene.add(portal2);
	d_scene.add(portal1);

	d_screenElements.push_back(d_debugText);


	d_player.setPosition(glm::vec3(0.0f, 4.0f, 5.0f));
}