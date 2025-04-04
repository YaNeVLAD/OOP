#pragma once
#include "ICanvas.h"

class MockCanvas : public ICanvas
{
public:
	void DrawLine(Point from, Point to, Color lineColor) const override;
	void FillPolygon(const std::vector<Point>& points, Color fillColor) const override;
	void DrawCircle(Point center, double radius, Color lineColor) const override;
	void FillCircle(Point center, double radius, Color fillColor) const override;
};
