#include "debugtext.ih"

DebugText::DebugText(glm::vec3 const &coords)
:
	Text(),
	ScreenElement(Text::shaderProgram()),
	d_coords(coords)
{}