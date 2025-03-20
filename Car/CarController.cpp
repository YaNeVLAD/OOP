#include "CarController.h"

#include <functional>
#include <sstream>
#include <unordered_map>

const std::unordered_map<std::string, bool (Car::*)()> NO_ARG_COMMANDS = {
	{ "EngineOn", &Car::TurnOnEngine },
	{ "EngineOff", &Car::TurnOffEngine },
};

const std::unordered_map<std::string, bool (Car::*)(int)> ARG_COMMANDS = {
	{ "SetGear", &Car::SetGear },
	{ "SetSpeed", &Car::SetSpeed },
};

CarController::CarController(std::istream& in, std::ostream& m_output)
	: m_input(in)
	, m_output(m_output)
{
}

void CarController::ExecuteCommand(const std::string& line)
{
	std::istringstream iss(line);
	std::string command;
	int arg;

	iss >> command;

	if (auto it = NO_ARG_COMMANDS.find(command); it != NO_ARG_COMMANDS.end())
	{
		if (!std::invoke(it->second, m_car))
		{
			m_output << "Car must be stopped and in neutral gear\n";
		}
		return;
	}

	if (auto it = ARG_COMMANDS.find(command); it != ARG_COMMANDS.end())
	{
		if (!(iss >> arg))
		{
			m_output << "Invalid command argument\n";
			return;
		}

		if (!std::invoke(it->second, m_car, arg))
		{
			if (command == "SetGear")
			{
				return PrintSetGearError(arg);
			}

			if (command == "SetSpeed")
			{
				return PrintSetSpeedError(arg);
			}
		}
		return;
	}

	if (command == "Info")
	{
		PrintInfo();
		return;
	}

	m_output << "Unknown command\n";
}

void CarController::PrintInfo()
{
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << "\n";
	m_output << "Direction: ";
	switch (m_car.GetDirection())
	{
	case Car::Direction::Backward:
		m_output << "backward";
		break;
	case Car::Direction::Still:
		m_output << "standing still";
		break;
	case Car::Direction::Forward:
		m_output << "forward";
		break;
	}
	m_output << "\n";
	m_output << "Speed: " << m_car.GetSpeed() << "\n";
	m_output << "Gear: " << static_cast<int>(m_car.GetGear());
	m_output << std::endl;
}

void CarController::PrintSetGearError(int arg)
{
	Car::Gear gear = static_cast<Car::Gear>(arg);
	bool isReverse = gear == Car::Gear::Reverse;

	if (arg < -1 || arg > 5)
	{
		m_output << "Invalid gear";
	}
	else if (!m_car.IsTurnedOn())
	{
		m_output << "Cannot set gear while engine is off";
	}
	else if (isReverse && m_car.GetSpeed() > 0)
	{
		m_output << "Cannot reverse while moving";
	}
	else
	{
		m_output << "Unsuitable current speed";
	}
	m_output << std::endl;
}

void CarController::PrintSetSpeedError(int arg)
{
	if (arg < 0)
	{
		m_output << "Speed cannot be negative";
	}
	else if (!m_car.IsTurnedOn())
	{
		m_output << "Cannot set speed while engine is off";
	}
	else if (m_car.GetGear() == Car::Gear::Neutral && arg > m_car.GetSpeed())
	{
		m_output << "Cannot accelerate on neutral";
	}
	else
	{
		m_output << "Speed is out of gear range";
	}
	m_output << std::endl;
}
