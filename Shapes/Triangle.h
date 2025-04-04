#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Triangle : public ISolidShape
{
public:
	Triangle(Point a, Point b, Point c);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();
};
