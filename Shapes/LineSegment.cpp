#include "LineSegment.h"
#include <format>

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
	return m_start.DistanceTo(m_end);
}

std::string LineSegment::ToString() const
{
	return std::format(
		"LineSegment:\n"
		"  Start: ({:.2f}, {:.2f})\n"
		"  End: ({:.2f}, {:.2f})\n"
		"  Length: {:.2f}\n"
		"  Outline color: {:08X}\n",
		m_start.x, m_start.y,
		m_end.x, m_end.y,
		m_start.DistanceTo(m_end),
		m_outlineColor.ToInt());
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

void LineSegment::Draw(const ICanvas& canvas) const
{
	canvas.DrawLine(m_start, m_end, m_outlineColor);
}
