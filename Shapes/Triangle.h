#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"
#include "Point.h"

class Triangle
	: public ISolidShape
	, public ICanvasDrawable
{
public:
	Triangle(Point a, Point b, Point c);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;

	void Draw(const ICanvas& canvas) override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();
};
