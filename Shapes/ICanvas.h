#pragma once
#include "Point.h"
#include <cstdint>
#include <vector>

class ICanvas
{
	virtual void DrawLine(Point from, Point to, uint32_t lineColor) = 0;
	virtual void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(Point center, double radius, uint32_t fillColor) = 0;
};
