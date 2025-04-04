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
	Color GetOutlineColor() override;
	Color GetFillColor() override;

	void Draw(const ICanvas& canvas) override;

	Point GetCenter();
	double GetRadius();

private:
	Point m_center;
	double m_radius;
	Color m_fillColor;
	Color m_outlineColor;
};
