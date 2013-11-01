#include "game.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		// TODO: implement more general argument handling
		if (argc > 1 and string(argv[1]) == "-f")
		{
			Game game;
			game.run();
		}
		else
		{
			Game game(1024, 768);
			game.run();
		}
	}
	catch (string &str)
	{
		cout << "Error starting game: " << str << endl;
	}
}
