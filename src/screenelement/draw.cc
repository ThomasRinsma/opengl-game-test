#include "screenelement.ih"

void ScreenElement::draw()
{
	drawImpl(glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
}