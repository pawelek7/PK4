#include <cstdlib>
#include <iostream>

#include "Game.h"

void Messagebox(const std::string & information)
{
#ifdef _WIN32
	Messagebox(information.c_str());
#endif
}

int main(int argc, char *argv[]) try
{

	Game SimCity2D;
	SimCity2D.RunGame();

	system("pause");

	return EXIT_SUCCESS;
}
catch (std::exception & exception)
{
	Messagebox(exception.what());
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "Unrecognised error. Please restart application." << std::endl;
}