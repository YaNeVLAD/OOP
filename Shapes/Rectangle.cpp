#include "Rectangle.h"

Rectangle::Rectangle(Point left, Point top, Point right, Point bottom)
{
}

double Rectangle::GetArea() const
{
	return 0.0;
}

double Rectangle::GetPerimeter() const
{
	return 0.0;
}

std::string Rectangle::ToString() const
{
	return std::string();
}

Color Rectangle::GetOutlineColor() const
{
	return 0;
}

Color Rectangle::GetFillColor() const
{
	return 0;
}

Point Rectangle::GetLeftTop()
{
	return Point();
}

Point Rectangle::GetRightBottom()
{
	return Point();
}

double Rectangle::GetWidth()
{
	return 0.0;
}

double Rectangle::GetHeight()
{
	return 0.0;
}

void Rectangle::Draw(const ICanvas& canvas)
{
}
