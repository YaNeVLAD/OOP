#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle(Point center, double radius);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	Point GetCenter();
	double GetRadius();
};
