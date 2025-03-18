#include "Car.h"
#include <functional>
#include <iostream>
#include <sstream>

const std::unordered_map<std::string, bool (Car::*)()> NO_ARG_COMMANDS = {
	{ "EngineOn", &Car::TurnOnEngine },
	{ "EngineOff", &Car::TurnOffEngine },
};

const std::unordered_map<std::string, bool (Car::*)(int)> ARG_COMMANDS = {
	{ "SetGear", &Car::SetGear },
	{ "SetSpeed", &Car::SetSpeed },
};

void PrintInfo(const Car& car)
{
	std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl;
	std::cout << "Direction: ";
	switch (car.GetDirection())
	{
	case Car::Direction::Backward:
		std::cout << "backward";
		break;
	case Car::Direction::Still:
		std::cout << "standing still";
		break;
	case Car::Direction::Forward:
		std::cout << "forward";
		break;
	default:
		std::cout << "unknown";
		break;
	}
	std::cout << std::endl;
	std::cout << "Speed: " << car.GetSpeed() << std::endl;
	std::cout << "Gear: " << static_cast<int>(car.GetGear()) << std::endl;
}

int main()
{
	Car car;

	int arg = 0;
	std::string line;
	std::string command;
	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		iss >> command;

		if (auto it = NO_ARG_COMMANDS.find(command); it != NO_ARG_COMMANDS.end())
		{
			std::invoke(it->second, car);
			continue;
		}

		if (auto it = ARG_COMMANDS.find(command); it != ARG_COMMANDS.end())
		{
			if (!(iss >> arg))
			{
				std::cout << "Invalid command argument" << std::endl;
				continue;
			}

			std::invoke(it->second, car, arg);
			continue;
		}

		if (command == "Info")
		{
			PrintInfo(car);
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	}

	return EXIT_SUCCESS;
}
