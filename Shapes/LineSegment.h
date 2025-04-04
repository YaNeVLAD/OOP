#pragma once
#include "ICanvasDrawable.h"
#include "IShape.h"
#include "Point.h"

class LineSegment
	: public IShape
	, public ICanvasDrawable
{
public:
	LineSegment(Point start, Point end);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	Color GetOutlineColor() override;

	void Draw(const ICanvas& canvas) override;

	Point GetStartPoint();
	Point GetEndPoint();
};
