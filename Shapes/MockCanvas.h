#pragma once
#include "ICanvas.h"

#include <ostream>

class MockCanvas : public ICanvas
{
public:
	explicit MockCanvas(std::ostream& output);

	void DrawLine(Point from, Point to, Color lineColor) const override;
	void FillPolygon(const std::vector<Point>& points, Color fillColor) const override;
	void DrawCircle(Point center, double radius, Color lineColor) const override;
	void FillCircle(Point center, double radius, Color fillColor) const override;

private:
	std::ostream& m_output;
};
