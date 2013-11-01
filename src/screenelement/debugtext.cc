#include "debugtext.h"
#include <sstream>

using namespace std;

DebugText::DebugText(glm::vec3 const &playerPosition)
:
	Text(),
	ScreenElement(Text::shaderProgram()),
	d_playerPosition(playerPosition)
{}

void DebugText::updateImpl(float deltaTime)
{
	ostringstream oss;
	oss << "FPS: ^2" << d_fps << "^7\n\n"
		<< "X: ^3" << d_playerPosition.x << "^7\n"
		<< "Y: ^3" << d_playerPosition.y << "^7\n"
		<< "Z: ^3" << d_playerPosition.z << "^7\n";

	// Set Text's string
	setText(oss.str());
}