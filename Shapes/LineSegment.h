#pragma once
#include "BaseShape.h"
#include "ICanvasDrawable.h"
#include "Point.h"

class LineSegment
	: public BaseShape
	, public ICanvasDrawable
{
public:
	LineSegment() = default;
	LineSegment(Point start, Point end, Color outlineColor = Color::White);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(const ICanvas& canvas) const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_start;
	Point m_end;
};
