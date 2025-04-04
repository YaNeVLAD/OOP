#pragma once
#include "ICanvas.h"

class MockCanvas : public ICanvas
{
	void DrawLine(Point from, Point to, uint32_t lineColor) override;
	void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) override;
	void DrawCircle(Point center, double radius, uint32_t lineColor) override;
	void FillCircle(Point center, double radius, uint32_t fillColor) override;
};
