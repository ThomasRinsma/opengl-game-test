#include "controller.ih"

void Controller::update(float deltaTime)
{
	if (not d_enabled)
		return;

	// Loop through all pending events
	sf::Event event;
	while (d_win.pollEvent(event))
	{
		processEvent(event);
	}
}