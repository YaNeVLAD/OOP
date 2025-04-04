#include "Rectangle.h"

Rectangle::Rectangle(Point left, Point top, Point right, Point bottom)
{
}

double Rectangle::GetArea()
{
	return 0.0;
}

double Rectangle::GetPerimeter()
{
	return 0.0;
}

std::string Rectangle::ToString()
{
	return std::string();
}

Color Rectangle::GetOutlineColor()
{
	return 0;
}

Color Rectangle::GetFillColor()
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
