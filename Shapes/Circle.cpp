#include "Circle.h"

Circle::Circle(Point center, double radius)
{
}

double Circle::GetArea() const
{
	return 0.0;
}

double Circle::GetPerimeter() const
{
	return 0.0;
}

std::string Circle::ToString() const
{
	return std::string();
}

Color Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

Color Circle::GetFillColor() const
{
	return m_fillColor;
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

void Circle::Draw(const ICanvas& canvas)
{
}
