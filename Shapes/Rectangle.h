#pragma once
#include "BaseSolidShape.h"
#include "ICanvasDrawable.h"
#include "Point.h"

class Rectangle
	: public BaseSolidShape
	, public ICanvasDrawable
{
public:
	Rectangle() = default;
	Rectangle(Point leftTop, Point rightBottom, Color fillColor = Color::White, Color outlineColor = Color::Transparent);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(const ICanvas& canvas) const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
