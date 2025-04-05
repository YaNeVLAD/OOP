#include "MockCanvas.h"

#include <format>

MockCanvas::MockCanvas(std::ostream& output)
	: m_output(output)
{
}

void MockCanvas::DrawLine(Point from, Point to, Color lineColor) const
{
	m_output << std::format(
		"DrawLine: from ({:.1f}, {:.1f}) to ({:.1f}, {:.1f}), color {:08X}\n",
		from.x, from.y,
		to.x, to.y,
		lineColor.ToInt());
}

void MockCanvas::FillPolygon(const std::vector<Point>& points, Color fillColor) const
{
	m_output << "FillPolygon: vertices [";
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (i > 0)
			m_output << ", ";
		m_output << std::format("({:.1f}, {:.1f})", points[i].x, points[i].y);
	}
	m_output << std::format("], color {:08X}\n", fillColor.ToInt());
}

void MockCanvas::DrawCircle(Point center, double radius, Color lineColor) const
{
	m_output << std::format(
		"DrawCircle: center ({:.1f}, {:.1f}), radius {:.1f}, color {:08X}\n",
		center.x, center.y,
		radius,
		lineColor.ToInt());
}

void MockCanvas::FillCircle(Point center, double radius, Color fillColor) const
{
	m_output << std::format(
		"FillCircle: center ({:.1f}, {:.1f}), radius {:.1f}, color {:08X}\n",
		center.x, center.y,
		radius,
		fillColor.ToInt());
}
