#include "debugtext.ih"

DebugText::DebugText(glm::vec3 const &playerPosition)
:
	Text(),
	ScreenElement(Text::shaderProgram()),
	d_playerPosition(playerPosition)
{}