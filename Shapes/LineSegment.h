#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	LineSegment(Point start, Point end);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

	Point GetStartPoint();
	Point GetEndPoint();
};
