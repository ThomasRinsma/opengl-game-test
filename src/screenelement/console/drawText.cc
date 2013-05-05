#include "console.ih"

void Console::drawText(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	glm::mat4 d_consoleTextModelMat = glm::scale(
		glm::translate(
			glm::mat4(1.0f), glm::vec3(d_position.x + 4.0f, d_position.y - 20.0f, 0.0f)
		),
		glm::vec3(16.0f, 16.0f, 1.0f)
	);

	
	d_consoleText.setModelMat(d_consoleTextModelMat);
	d_consoleText.draw(viewMat, projMat);
}