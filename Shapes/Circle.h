#pragma once
#include "BaseSolidShape.h"
#include "ICanvasDrawable.h"
#include "Point.h"

class Circle
	: public BaseSolidShape
	, public ICanvasDrawable
{
public:
	Circle() = default;
	Circle(Point center, double radius, Color fillColor = Color::White, Color outlineColor = Color::Transparent);
	~Circle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(const ICanvas& canvas) const override;

	Point GetCenter() const;
	double GetRadius() const;

private:
	Point m_center;
	double m_radius;
};
