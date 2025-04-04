#pragma once
#include "Color.h"
#include "Point.h"
#include <cstdint>
#include <vector>

class ICanvas
{
	virtual void DrawLine(Point from, Point to, Color lineColor) = 0;
	virtual void FillPolygon(const std::vector<Point>& points, Color fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, Color lineColor) = 0;
	virtual void FillCircle(Point center, double radius, Color fillColor) = 0;
};
