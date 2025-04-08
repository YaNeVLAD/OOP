#pragma once
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"

#include <istream>
#include <memory>

class ShapeParser
{
public:
	explicit ShapeParser(std::istream& input);

	std::vector<std::unique_ptr<BaseShape>> Parse();

private:
	std::unique_ptr<Circle> ParseCircle(std::istream& input);
	std::unique_ptr<LineSegment> ParseLineSegment(std::istream& input);
	std::unique_ptr<Rectangle> ParseRectangle(std::istream& input);
	std::unique_ptr<Triangle> ParseTriangle(std::istream& input);

	std::istream& m_input;
};
