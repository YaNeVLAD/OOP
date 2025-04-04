#include "MockCanvas.h"

MockCanvas::MockCanvas(std::ostream& output)
	: m_output(output)
{
}

void MockCanvas::DrawLine(Point from, Point to, Color lineColor) const
{
}

void MockCanvas::FillPolygon(const std::vector<Point>& points, Color fillColor) const
{
}

void MockCanvas::DrawCircle(Point center, double radius, Color lineColor) const
{
}

void MockCanvas::FillCircle(Point center, double radius, Color fillColor) const
{
}
