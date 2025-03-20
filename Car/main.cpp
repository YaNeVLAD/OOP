#include <iostream>
#include <string>

#include "CarController.h"

int main()
{
	CarController controller(std::cout);

	std::string line;
	while (std::getline(std::cin, line))
	{
		controller.ExecuteCommand(line);
	}

	return EXIT_SUCCESS;
}
