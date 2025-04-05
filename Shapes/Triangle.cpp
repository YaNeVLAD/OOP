#include "Triangle.h"
#include <format>

Triangle::Triangle(Point a, Point b, Point c, Color fillColor, Color outlineColor)
	: m_p0(a)
	, m_p1(b)
	, m_p2(c)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

double Triangle::GetArea() const
{
	auto [a, b, c] = GetLinesLength();

	double p = (a + b + c) / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::GetPerimeter() const
{
	auto [a, b, c] = GetLinesLength();

	return (a + b + c);
}

std::string Triangle::ToString() const
{
	return std::format(
		"Triangle:\n"
		"  Vertex 1: ({:.2f}, {:.2f})\n"
		"  Vertex 2: ({:.2f}, {:.2f})\n"
		"  Vertex 3: ({:.2f}, {:.2f})\n"
		"  Area: {:.2f}\n"
		"  Perimeter: {:.2f}\n"
		"  Fill color: {:08X}\n"
		"  Outline color: {:08X}\n",
		m_p0.x, m_p0.y,
		m_p1.x, m_p1.y,
		m_p2.x, m_p2.y,
		GetArea(),
		GetPerimeter(),
		m_fillColor.ToInt(),
		m_outlineColor.ToInt());
}

Color Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

Color Triangle::GetFillColor() const
{
	return m_fillColor;
}

Point Triangle::GetVertex1() const
{
	return m_p0;
}

Point Triangle::GetVertex2() const
{
	return m_p1;
}

Point Triangle::GetVertex3() const
{
	return m_p2;
}

std::tuple<double, double, double> Triangle::GetLinesLength() const
{
	double a = m_p0.DistanceTo(m_p1);
	double b = m_p1.DistanceTo(m_p2);
	double c = m_p2.DistanceTo(m_p0);

	return { a, b, c };
}

void Triangle::Draw(const ICanvas& canvas) const
{
	canvas.FillPolygon({ m_p0, m_p1, m_p2 }, m_fillColor);
	canvas.DrawPolygon({ m_p0, m_p1, m_p2 }, m_outlineColor);
}
