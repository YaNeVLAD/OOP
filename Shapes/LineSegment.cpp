#include "LineSegment.h"

LineSegment::LineSegment(Point a, Point b)
{
}

double LineSegment::GetArea()
{
	return 0.0;
}

double LineSegment::GetPerimeter()
{
	return 0.0;
}

std::string LineSegment::ToString()
{
	return std::string();
}

uint32_t LineSegment::GetOutlineColor()
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
