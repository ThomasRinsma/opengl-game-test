#include "game.ih"

void Game::stepGame()
{
	if (not d_running)
		return;

	// TODO
	float mouseSpeed = 0.001f * M_PI; // radians per pixel
	float moveSpeed = 2.0f; // units per second

	int latMovement = d_controller->moveRight() * 1.0f - d_controller->moveLeft() * 1.0f;
	int longMovement = d_controller->moveForward() * 1.0f - d_controller->moveBack() * 1.0f;

	float latSpeed = 1.0f;
	float longSpeed = 1.0f;

	// Mouse stuff
	vec2 mousePosDelta = d_controller->mousePosition() - vec2(d_win->GetWidth() / 2, d_win->GetHeight() / 2);

	//cout << "mouseDeltaX: " << mousePosDelta.x << ", mouseDeltaY: " << mousePosDelta.y << endl;
	d_player.setYaw(d_player.yaw() - mousePosDelta.x * mouseSpeed);
	d_player.setPitch(d_player.pitch() - mousePosDelta.y * mouseSpeed);

	// Reset cursor to center
	d_win->SetCursorPosition(d_win->GetWidth() / 2, d_win->GetHeight() / 2);

	d_player.setRelativeVelocity(vec3(latMovement * latSpeed, 0.0f, longMovement * longSpeed)); // TODO: up/down
	d_player.integratePosition(d_win->GetFrameTime() * moveSpeed);
}
