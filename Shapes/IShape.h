#pragma once

#include <cstdint>
#include <string>

class IShape
{
	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString() = 0;
	virtual Color GetOutlineColor() = 0;
};
