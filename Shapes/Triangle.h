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

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	void Draw(const ICanvas& canvas) override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();
};
