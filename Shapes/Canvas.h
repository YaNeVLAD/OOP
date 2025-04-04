#pragma once
#include "ICanvas.h"

class Canvas : public ICanvas
{
	void DrawLine(Point from, Point to, Color lineColor) override;
	void FillPolygon(const std::vector<Point>& points, Color fillColor) override;
	void DrawCircle(Point center, double radius, Color lineColor) override;
	void FillCircle(Point center, double radius, Color fillColor) override;
};
