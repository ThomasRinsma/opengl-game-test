#include "game.ih"

void Game::initGame()
{
	d_debugText = new Text2D(*d_shaderPrograms[2], glm::vec2(4.0f, d_winHeight - 20.0f), glm::vec2(2.0f), "");
	Grid* grid = new Grid(*d_shaderPrograms[0]);
	Model* room = new Model(*d_shaderPrograms[1], "wall", "inverted_cube");
	Model* monkey = new Model(*d_shaderPrograms[1], "wall", "monkey");
	Cube* cube = new Cube(*d_shaderPrograms[1], "crate");

	Portal *portal1 = new Portal(*d_shaderPrograms[0]);
	Portal *portal2 = new Portal(*d_shaderPrograms[0]);

	Portal *portal3 = new Portal(*d_shaderPrograms[0]);
	Portal *portal4 = new Portal(*d_shaderPrograms[0]);

	Portal *portal5 = new Portal(*d_shaderPrograms[0]);
	Portal *portal6 = new Portal(*d_shaderPrograms[0]);

	Portal *portal7 = new Portal(*d_shaderPrograms[0]);
	Portal *portal8 = new Portal(*d_shaderPrograms[0]);

	Portal *portal9 = new Portal(*d_shaderPrograms[0]);
	Portal *portal10 = new Portal(*d_shaderPrograms[0]);


	portal1->setDestination(portal2);
	portal2->setDestination(portal4);

	portal3->setDestination(portal4);
	portal4->setDestination(portal2);

	portal5->setDestination(portal6);
	portal6->setDestination(portal6);

	portal7->setDestination(portal8);
	portal8->setDestination(portal8);

	portal9->setDestination(portal10);
	portal10->setDestination(portal10);


	portal1->setPosition(glm::vec3(0.50f, 1.5f, 3.0f));
	portal2->setPosition(glm::vec3( 7.499f, 6.0f, 0.0f));
	portal1->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI/2.0f, true); // crate right side
	portal2->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI/2.0f, true); // right wall
	portal2->setScale(glm::vec3(15.0f, 10.0f, 15.0f));

	portal3->setPosition(glm::vec3(-0.50f, 1.5f, 3.0f));
	portal4->setPosition(glm::vec3(-7.499f, 6.0f, 0.0f));
	portal3->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI/2.0f, true); // crate left side
	portal4->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI/2.0f, true); // left wall
	portal4->setScale(glm::vec3(15.0f, 10.0f, 15.0f));

	portal5->setPosition(glm::vec3(0.0f, 1.5f, 3.50f));
	portal6->setPosition(glm::vec3( 0.0f, 6.0f, 7.499f));
	portal5->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, true); // crate back side
	portal6->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI, true); // back wall
	portal6->setScale(glm::vec3(15.0f, 10.0f, 15.0f));

	portal7->setPosition(glm::vec3(0.0f, 1.5f, 2.50f));
	portal8->setPosition(glm::vec3( 0.0f, 6.0f, -7.499f));
	portal7->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI, true); // crate back side
	portal8->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, true); // back wall
	portal8->setScale(glm::vec3(15.0f, 10.0f, 15.0f));

	portal9->setPosition(glm::vec3(0.0f, 2.00f, 3.0f));
	portal10->setPosition(glm::vec3( 0.0f, 10.99f, 0.0f));
	portal9->addOrientation(glm::vec3(1.0f, 0.0f, 0.0f), -M_PI/2.0f, true); // crate right side
	portal9->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI, true); // crate right side
	portal10->addOrientation(glm::vec3(1.0f, 0.0f, 0.0f), M_PI/2.0f, true); // right wall
	portal10->setScale(glm::vec3(15.0f, 15.0f, 15.0f));



	
	cube->setPosition(glm::vec3(0.0f, 1.5f, 3.0f));
	monkey->setPosition(glm::vec3(0.0f, 2.0f, -3.0f));
	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized

	d_scene.add(grid);
	d_scene.add(room);
	//d_scene.add(cube);
	d_scene.add(monkey);

	d_scene.add(portal1);
	d_scene.add(portal2);

	d_scene.add(portal3);
	d_scene.add(portal4);

	d_scene.add(portal5);
	d_scene.add(portal6);

	d_scene.add(portal7);
	d_scene.add(portal8);

	d_scene.add(portal9);
	d_scene.add(portal10);

	d_screenElements.push_back(d_debugText);


	d_player.setPosition(glm::vec3(0.0f, 4.0f, 5.0f));
}