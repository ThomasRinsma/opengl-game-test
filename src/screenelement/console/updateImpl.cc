#include "console.ih"
#include <iostream>
void Console::updateImpl(float deltaTime)
{

	if (d_controller.toggleConsole())
	{
		d_consoleDown = not d_consoleDown;

		if (d_consoleDown)
			d_controller.disable();
		else
			d_controller.enable();
	}

	// The console is down
	if (d_consoleDown)
	{
		// Capture key presses
		sf::Event event;
		while (d_win.pollEvent(event))
		{
			// If it's ascii and not ESC
			if (event.type == sf::Event::TextEntered and event.text.unicode < 128 and event.text.unicode != 27)
			{
				char c = static_cast<char>(event.text.unicode);

				// Backspace pressed, and string not empty
				if (c == 8 and d_inputLine.size() > 0)
					d_inputLine.pop_back(); // yay c++11

				// Readable character
				if (c >= ' ' and c <= '~')
					d_inputLine.push_back(c);

				// Enter was pressed
				if ((c == '\n' || c == '\r') and d_inputLine.size() > 0)
				{
					d_lines.push_front("^7You entered: " + d_inputLine);

					d_inputLine.clear();
				}

				cout << "char: " << (int)c << endl;
				
			}
			else
				d_controller.processEvent(event);
		}

		// Generate new text, 14 lines of history plus the input line
		string totalText;

		// Concatenate all history lines in the queue
		for (int idx = 13; idx >= 0; --idx)
			totalText += d_lines[idx] + "\n";

		// Append the current input line
		totalText += "^1> ^7" + d_inputLine;

		// Blink time!
		if (d_timeSinceBlink > 0.5f)
		{
			d_cursorState = not d_cursorState;
			d_timeSinceBlink = 0.0f;
		}

		// Draw white cursor every other second
		if (d_cursorState)
			totalText += "^7_";

		// Update counter, # of seconds since last blink
		d_timeSinceBlink += deltaTime;

		// Submit string to Text object
		d_consoleText.setText(totalText);
	}
	//d_consoleText.setText("^7Line 1\nLine 2\nLine 3\nLine 4\nLine 5\nLine 6\nLine 7\nLine 8\nLine 9\nLine 10\nLine 1\nLine 2\nLine 3\nLine 4\nLine 5");
}