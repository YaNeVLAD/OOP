#pragma once
#include "ICanvasDrawable.h"
#include "IShape.h"
#include "Point.h"

class LineSegment
	: public IShape
	, public ICanvasDrawable
{
public:
	LineSegment(Point start, Point end, Color outlineColor = Color::White);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Color GetOutlineColor() const override;

	void Draw(const ICanvas& canvas) override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_start;
	Point m_end;
	Color m_outlineColor;
};
