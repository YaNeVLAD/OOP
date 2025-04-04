#include "LineSegment.h"

LineSegment::LineSegment(Point a, Point b)
{
}

double LineSegment::GetArea() const
{
	return 0.0;
}

double LineSegment::GetPerimeter() const
{
	return 0.0;
}

std::string LineSegment::ToString() const
{
	return std::string();
}

Color LineSegment::GetOutlineColor() const
{
	return 0;
}

Point LineSegment::GetStartPoint()
{
	return Point();
}

Point LineSegment::GetEndPoint()
{
	return Point();
}

void LineSegment::Draw(const ICanvas& canvas)
{
}
