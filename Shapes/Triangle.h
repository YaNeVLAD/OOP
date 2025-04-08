#pragma once
#include "BaseSolidShape.h"
#include "ICanvasDrawable.h"
#include "Point.h"

#include <tuple>

class Triangle
	: public BaseSolidShape
	, public ICanvasDrawable
{
public:
	Triangle() = default;
	Triangle(Point a, Point b, Point c, Color fillColor = Color::White, Color outlineColor = Color::Transparent);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(const ICanvas& canvas) const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	std::tuple<double, double, double> GetLinesLength() const;

	Point m_p0;
	Point m_p1;
	Point m_p2;
};
