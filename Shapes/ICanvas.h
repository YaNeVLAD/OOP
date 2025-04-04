#pragma once
#include "Color.h"
#include "Point.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to, Color lineColor) const = 0;
	virtual void DrawPolygon(const std::vector<Point>& points, Color lineColor) const = 0;
	virtual void FillPolygon(const std::vector<Point>& points, Color fillColor) const = 0;
	virtual void DrawCircle(Point center, double radius, Color lineColor) const = 0;
	virtual void FillCircle(Point center, double radius, Color fillColor) const = 0;
};
