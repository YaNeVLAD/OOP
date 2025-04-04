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

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;

	void Draw(const ICanvas& canvas) override;

	Point GetCenter() const;
	double GetRadius() const;

private:
	Point m_center;
	double m_radius;
	Color m_fillColor;
	Color m_outlineColor;
};
