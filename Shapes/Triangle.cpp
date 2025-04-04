#include "Triangle.h"

Triangle::Triangle(Point a, Point b, Point c)
{
}

double Triangle::GetArea()
{
	return 0.0;
}

double Triangle::GetPerimeter()
{
	return 0.0;
}

std::string Triangle::ToString()
{
	return std::string();
}

uint32_t Triangle::GetOutlineColor()
{
	return 0;
}

uint32_t Triangle::GetFillColor()
{
	return 0;
}

Point Triangle::GetVertex1()
{
	return Point();
}

Point Triangle::GetVertex2()
{
	return Point();
}

Point Triangle::GetVertex3()
{
	return Point();
}

void Triangle::Draw(const ICanvas& canvas)
{
}
