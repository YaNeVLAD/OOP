#pragma once

#include <istream>
#include <ostream>

#include "Car.h"

class CarController
{
public:
	CarController(std::istream& in, std::ostream& out);

	void ExecuteCommand(const std::string& line);

private:
	Car m_car;

	std::istream& m_input;
	std::ostream& m_output;

	void PrintInfo();

	void PrintSetGearError(int arg);
	void PrintSetSpeedError(int arg);
};
