#include "Rectangle.h"
#include <format>

Rectangle::Rectangle(Point leftTop, Point rightBottom, Color fillColor, Color outlineColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, BaseSolidShape(fillColor, outlineColor)
{
}

double Rectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double Rectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string Rectangle::ToString() const
{
	return std::format(
			   "Rectangle:\n"
			   "  Left Top: ({:.2f}, {:.2f})\n"
			   "  Right Bottom: ({:.2f}, {:.2f})\n"
			   "  Width: {:.2f}\n"
			   "  Height: {:.2f}\n",
			   m_leftTop.x, m_leftTop.y,
			   m_rightBottom.x, m_rightBottom.y,
			   GetWidth(),
			   GetHeight())
		+ BaseSolidShape::ToString();
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double Rectangle::GetWidth() const
{
	return abs(m_rightBottom.x - m_leftTop.x);
}

double Rectangle::GetHeight() const
{
	return abs(m_rightBottom.y - m_leftTop.y);
}

void Rectangle::Draw(const ICanvas& canvas) const
{
	std::vector<Point> vertices = {
		m_leftTop,
		{ m_rightBottom.x, m_leftTop.y },
		m_rightBottom,
		{ m_leftTop.x, m_rightBottom.y }
	};

	canvas.FillPolygon(vertices, GetFillColor());
	canvas.DrawPolygon(vertices, GetOutlineColor());
}
