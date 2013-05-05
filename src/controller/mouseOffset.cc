#include "controller.ih"

glm::vec2 Controller::mouseOffset()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(d_win);
	sf::Vector2i winCenter(d_win.getSize().x / 2, d_win.getSize().y / 2);

	sf::Mouse::setPosition(winCenter, d_win);

	if (d_enabled)
		return glm::vec2(mousePos.x - winCenter.x, mousePos.y - winCenter.y);
	else
		return glm::vec2(0.0f, 0.0f);
}