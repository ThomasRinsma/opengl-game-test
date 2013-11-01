#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "sceneobject/cube.h"
#include "sceneobject/grid.h"
#include "sceneobject/genericmodel.h"
#include "sceneobject/portal.h"

#include "collidable/collidableplane.h"
#include "resourcemanager.h"
#include "light.h"

#include "screenelement/debugtext.h"
#include "screenelement/console.h"

#include "game.h"

using namespace std;

string const windowTitle = "OpenGL Test";

Game::Game()
:
	d_fullscreen(true),
	d_win(sf::VideoMode::getDesktopMode(), windowTitle, sf::Style::Fullscreen, sf::ContextSettings(24, 8, 0, 3, 2)),
	d_controller(d_win),
	d_player(d_controller),
	d_scene(d_player),
	d_gui(d_win)
{
	initWindow();
	initGraphics();
	initGame();
}

Game::Game(size_t width, size_t height)
:
	d_fullscreen(false),
	d_win(sf::VideoMode(width, height), windowTitle, sf::Style::Close, sf::ContextSettings(24, 8, 0, 3, 2)),
	d_controller(d_win),
	d_player(d_controller),
	d_scene(d_player),
	d_gui(d_win)
{
	initWindow();
	initGraphics();
	initGame();
}

Game::~Game()
{
	d_win.close();
}

void Game::initGame()
{
	Console *console = new Console(d_controller, d_win);

	console->printLine("^7Welcome! Try entering 'help'.");

	DebugText *debugText = new DebugText(d_player.position());
	Grid* grid = new Grid();
	GenericModel* room = new GenericModel("wall", "inverted_cube");
	GenericModel* monkey = new GenericModel("monkeytex", "monkey");
	GenericModel* companion = new GenericModel("companion", "companion");
	Cube* cube = new Cube("crate");

	Portal *portal1 = new Portal();
	Portal *portal2 = new Portal();

	Light *light1 = new Light(glm::vec3(-5.0f, 4.0f, 0.0f));
	Light *light2 = new Light(glm::vec3(5.0f, 4.0f, 0.0f));
	Light *light3 = new Light(glm::vec3(0.0f, 4.0f, 3.0f));

	portal1->setDestination(portal2);
	portal2->setDestination(portal1);

	portal1->setPosition(glm::vec3(-2.0f, 1.5f, 0.5f));
	portal2->setPosition(glm::vec3( 2.0f, 1.5f, 0.5f));
	portal1->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI/2.0f, true);
	portal2->addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI/2.0f, true);

	portal1->setScale(glm::vec3(2.0));
	portal2->setScale(glm::vec3(2.0));

	// scale and position are in pixels
	// position is from the bottom left
	debugText->setScale(glm::vec3(16.0f, 16.0f, 1.0f));
	debugText->setPosition(glm::vec3(4.0f, 70.0f, 0.0f));

	// console has 100% width and 250px height (15 lines)
	console->setScale(glm::vec3(d_win.getSize().x, 250, 1.0f));
	// console position is the top left corner
	console->setPosition(glm::vec3(0.0f, d_win.getSize().y, 0.0f));

	
	cube->setPosition(glm::vec3(0.0f, 1.5f, 1.5f));
	monkey->setPosition(glm::vec3(0.0f, 2.0f, -3.0f));
	companion->setPosition(glm::vec3(0.0f, 1.5f, 0.0f));

	room->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	room->setScale(glm::vec3(15.0f, 10.0f, 15.0f)); // room sized


	// add floor collision
	//CollidablePlane floorCol(room, )

	d_scene.add("light1", light1);
	d_scene.add("light2", light2);
	d_scene.add("light3", light3);


	d_scene.add("grid", grid);
	d_scene.add("room", room);
	//d_scene.add("cube", cube);
	//d_scene.add("monkey", monkey);
	d_scene.add("companion", companion);

	d_scene.add("p1", portal1);
	d_scene.add("p2", portal2);

	d_gui.add("debugText", debugText);
	d_gui.add("console", console);
	
	d_player.setPosition(glm::vec3(0.0f, 4.0f, 5.0f));
}

void Game::initWindow()
{
	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win.setVerticalSyncEnabled(d_vsync);

	d_win.setKeyRepeatEnabled(false);
}

void Game::initGraphics()
{
	// Load all resources from files
	ResourceManager::instance().loadAll();

	d_player.setFov(45.0f);
	d_player.setScreenRatio(static_cast<float>(d_win.getSize().x) /
			static_cast<float>(d_win.getSize().y));
	d_player.setZnear(0.1f);
	d_player.setZfar(100.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// wireframe mode, because why not
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::stepGame()
{
	// Time since last step
	float deltaTime = d_timer.restart().asSeconds();

	// Update the controller
	d_controller.update(deltaTime);
	// Handle various window and focus states
	if (d_controller.closedWindow())
		stop();

	if (d_controller.lostFocus() and not d_paused)
		pause();

	if (d_controller.exit())
	{
		if (d_paused)
			stop();
		else
			pause();
	}

	if (d_controller.gainedFocus() and d_fullscreen and d_paused)
		unpause();

	if (d_controller.mouseLeft() and d_paused)
		unpause();

	// Toggle vsync if that key was pressed
	if (d_controller.toggleVsync())
	{
		d_vsync = not d_vsync;
		d_win.setVerticalSyncEnabled(d_vsync);
	}

	// Always update the GUI
	d_gui.update(deltaTime);

	// Update the rest
	if (not d_paused)
	{
		d_player.update(deltaTime);
		d_scene.update(deltaTime);

		// Update the fps counter for the debug text
		d_gui.get<DebugText>("debugText").setFPS(d_fps);
	}
}

void Game::draw()
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Draw scene
	d_scene.draw();

	// Draw GUI/HUD
	d_gui.draw();

	// Flip buffer
	d_win.display();
}

void Game::run()
{
	sf::Clock sfmlclock;
	float curSec = 2.0f, lastSec = 0.0f;
	size_t frames = 0;

	// The run-loop
	try
	{
		while (true)
		{
			stepGame();
			draw();

			// Calculate FPS
			curSec = sfmlclock.getElapsedTime().asSeconds();
			if (curSec - lastSec >= 1.0f)
			{
				lastSec = curSec;
				d_fps = frames;
				frames = 0;
			}

			++frames;
		}
	}
	catch (string &errorMsg)
	{
		cerr << "Error while running: " << errorMsg << endl;
	}
	catch (...)
	{
		// exit cleanly
	}

	d_win.close();
}