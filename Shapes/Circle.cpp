#include "Circle.h"

Circle::Circle(Point center, double radius)
{
}

double Circle::GetArea()
{
	return 0.0;
}

double Circle::GetPerimeter()
{
	return 0.0;
}

std::string Circle::ToString()
{
	return std::string();
}

Color Circle::GetOutlineColor()
{
	return m_outlineColor;
}

Color Circle::GetFillColor()
{
	return m_fillColor;
}

Point Circle::GetCenter()
{
	return m_center;
}

double Circle::GetRadius()
{
	return m_radius;
}

void Circle::Draw(const ICanvas& canvas)
{
}
