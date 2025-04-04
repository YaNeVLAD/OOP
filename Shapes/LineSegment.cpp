#include "LineSegment.h"

LineSegment::LineSegment(Point start, Point end, Color outlineColor)
	: m_start(start)
	, m_end(end)
	, m_outlineColor(outlineColor)
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
	return m_outlineColor;
}

Point LineSegment::GetStartPoint() const
{
	return m_start;
}

Point LineSegment::GetEndPoint() const
{
	return m_end;
}

void LineSegment::Draw(const ICanvas& canvas)
{
	canvas.DrawLine(m_start, m_end, m_outlineColor);
}
