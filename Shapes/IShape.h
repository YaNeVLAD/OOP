#pragma once

#include <cstdint>
#include <string>

class IShape
{
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual Color GetOutlineColor() const = 0;
};
