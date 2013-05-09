#include "game.ih"
#include <iostream>

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
