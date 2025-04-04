#include "Circle.h"

#define _USE_MATH_DEFINES
#include <format>
#include <math.h>

Circle::Circle(Point center, double radius, Color fillColor, Color outlineColor)
	: m_center(center)
	, m_radius(radius)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

double Circle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string Circle::ToString() const
{
	return std::format(
		"Circle:\n"
		"  Center: ({:.2f}, {:.2f})\n"
		"  Radius: {:.2f}\n"
		"  Area: {:.2f}\n"
		"  Perimeter: {:.2f}\n"
		"  Fill color: {:08X}\n"
		"  Outline color: {:08X}\n",
		m_center.x, m_center.y,
		m_radius,
		GetArea(),
		GetPerimeter(),
		m_fillColor.ToInt(),
		m_outlineColor.ToInt());
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

void Circle::Draw(const ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}
