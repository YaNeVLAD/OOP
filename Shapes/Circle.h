#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"
#include "Point.h"

class Circle
	: public ISolidShape
	, public ICanvasDrawable
{
public:
	Circle(Point center, double radius);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	void Draw(const ICanvas& canvas) override;

	Point GetCenter();
	double GetRadius();
};
