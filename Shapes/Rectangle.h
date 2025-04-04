#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Rectangle : public ISolidShape
{
public:
	Rectangle(Point left, Point top, Point right, Point bottom);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();
};
