#include "console.ih"
#include <iostream>

void Console::updateImpl(float deltaTime)
{

	if (d_controller.toggleConsole() and not d_toggleKeyDown)
	{
		d_toggleKeyDown = true;
		d_consoleDown = not d_consoleDown;
	}

	if (not d_controller.toggleConsole())
		d_toggleKeyDown = false;

	d_consoleText.setText("^7THIS IS THE CONSOLE TEXT");
}