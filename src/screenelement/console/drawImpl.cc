#include "console.ih"

void Console::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	if (d_consoleDown)
	{
		// Draw console background
		drawBackground(viewMat, projMat);

		// Draw console text
		drawText(viewMat, projMat);
	}
}