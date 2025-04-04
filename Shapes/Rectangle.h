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

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;

	void Draw(const ICanvas& canvas) override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();
};
