#include "Game.h"

void errorMessage(const std::string& message, const std::string& error);

int main(int argc, char* argv[]) try
{
	Game Simcity;
	Simcity.HoldGame();

	return EXIT_SUCCESS;
}
catch (std::exception & e)
{
	errorMessage(e.what(), "Error! Message: " + std::string(e.what()) + "\nPress enter to exit.\n");
	return EXIT_FAILURE;
}
catch (...)
{
	errorMessage("Unrecognised exception type.", "Error: Unrecognised exception type.\nPress enter to exit.\n");
	return EXIT_FAILURE;
}

void errorMessage(const std::string& message, const std::string& error)
{
#ifdef __WIN32
	MessageBox(nullptr, message.c_str(), "Error!", MB_OK);
#else
	std::cerr << error;
	std::cin.ignore();
#endif // __WIN32
}