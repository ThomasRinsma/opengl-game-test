#include "debugtext.ih"

void DebugText::updateImpl(float deltaTime)
{
	ostringstream oss;
	oss << "FPS: " << d_fps << "\n\n"
		<< "X: " << d_playerPosition.x << '\n'
		<< "Y: " << d_playerPosition.y << '\n'
		<< "Z: " << d_playerPosition.z << '\n';

	// Set Text's string
	setText(oss.str());
}