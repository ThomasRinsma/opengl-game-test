#include "screenelement.ih"

ScreenElement::ScreenElement(ShaderProgram &shaderProgram, glm::vec2 const &position)
:
	Drawable(shaderProgram),
	d_position(position)
{}
