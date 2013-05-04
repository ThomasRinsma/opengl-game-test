#include "game.ih"

void Game::initGame()
{
	DebugText *debugText = new DebugText(d_player.position());
	Grid* grid = new Grid();
	GenericModel* room = new GenericModel("wall", "inverted_cube");
	GenericModel* monkey = new GenericModel("monkeytex", "monkey");
	GenericModel* companion = new GenericModel("companion", "companion");
	Cube* cube = new Cube("crate");

	Portal *portal1 = new Portal();
	Portal *portal2 = new Portal();

	Light *light1 = new Light(glm::vec3(-5.0f, 4.0f, 0.0f), glm::vec3(2.0f, 0.5f, 0.0f));
	Light *light2 = new Light(glm::vec3(5.0f, 4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f));
	Light *light3 = new Light(glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3(1.0f));

	portal1->setDestination(portal2);
	portal2->setDestination(portal1);

	portal1->setPosition(glm::vec3(-3.0f, 1.5f, 0.0f));
	portal2->setPosition(glm::vec3( 3.0f, 1.5f, 0.0f));
	portal1->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI/2.0f, true);
	portal2->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI/2.0f, true);

	debugText->setScale(glm::vec3(16.0f, 16.0f, 1.0f));
	debugText->setPosition(glm::vec3(4.0f, d_win.getSize().y - 20.0f, 0.0f));

	
	cube->setPosition(glm::vec3(0.0f, 1.5f, 1.5f));
	monkey->setPosition(glm::vec3(0.0f, 2.0f, -3.0f));
	companion->setPosition(glm::vec3(0.0f, 2.0f, 3.0f));

	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized

	d_scene.add("light1", light1);
	d_scene.add("light2", light2);
	d_scene.add("light3", light3);


	d_scene.add("grid", grid);
	d_scene.add("room", room);
	d_scene.add("cube", cube);
	d_scene.add("monkey", monkey);
	d_scene.add("companion", companion);

	d_scene.add("p1", portal1);
	d_scene.add("p2", portal2);

	d_gui.add("debugText", debugText);
	
	d_player.setPosition(glm::vec3(0.0f, 4.0f, 5.0f));
}