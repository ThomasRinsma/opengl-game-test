#include "game/game.h"
#include <iostream>

using namespace std;

int main()
{
	try
	{
		Game game(1024, 768);
		game.run();
	}
	catch (string &str)
	{
		cout << "ERROR: " << str << endl;
	}
}
