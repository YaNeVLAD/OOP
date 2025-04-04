#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"
#include "Point.h"

class Rectangle
	: public ISolidShape
	, public ICanvasDrawable
{
public:
	Rectangle(Point left, Point top, Point right, Point bottom);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;

	void Draw(const ICanvas& canvas) override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();
};
