#include "console.ih"

void Console::printLine(std::string const &line)
{
	// TODO: length checking maybe, and/or auto wrapping
	d_lines.push_front(line);
}