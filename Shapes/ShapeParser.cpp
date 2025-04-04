#include "ShapeParser.h"
#include <sstream>

namespace shapes
{
constexpr const char* CIRCLE = "circle";
constexpr const char* LINE = "line";
constexpr const char* RECTANGLE = "rectangle";
constexpr const char* TRIANGLE = "triangle";
} // namespace shapes

ShapeParser::ShapeParser(std::istream& input)
	: m_input(input)
{
}

std::vector<std::unique_ptr<IShape>> ShapeParser::Parse()
{
	std::vector<std::unique_ptr<IShape>> shapes;

	std::string line;
	std::string shapeType;
	while (std::getline(m_input, line))
	{
		std::istringstream iss(line);

		iss >> shapeType;
		try
		{
			if (shapeType == shapes::CIRCLE)
			{
				shapes.push_back(ParseCircle(iss));
			}
			else if (shapeType == shapes::LINE)
			{
				shapes.push_back(ParseLineSegment(iss));
			}
			else if (shapeType == shapes::RECTANGLE)
			{
				shapes.push_back(ParseRectangle(iss));
			}
			else if (shapeType == shapes::TRIANGLE)
			{
				shapes.push_back(ParseTriangle(iss));
			}
		}
		catch (const std::exception&)
		{
			continue;
		}
	}

	return shapes;
}

std::unique_ptr<Circle> ShapeParser::ParseCircle(std::istream& input)
{
	Point center;
	double radius;
	Color fillColor;
	Color outlineColor;

	input >> center.x >> center.y >> radius;

	uint32_t color;
	if (input >> std::hex >> color)
	{
		fillColor = color;
	}
	if (input >> std::hex >> color)
	{
		outlineColor = color;
	}

	return std::make_unique<Circle>(center, radius, fillColor, outlineColor);
}

std::unique_ptr<LineSegment> ShapeParser::ParseLineSegment(std::istream& input)
{
	Point start, end;
	Color outlineColor = Color::White;

	input >> start.x >> start.y >> end.x >> end.y;

	uint32_t color;
	if (input >> std::hex >> color)
	{
		outlineColor = Color(color);
	}

	return std::make_unique<LineSegment>(start, end, outlineColor);
}

std::unique_ptr<Rectangle> ShapeParser::ParseRectangle(std::istream& input)
{
	Point leftTop, rightBottom;
	Color fillColor = Color::White;
	Color outlineColor = Color::Transparent;

	input >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y;

	uint32_t color;
	if (input >> std::hex >> color)
	{
		fillColor = Color(color);
	}
	if (input >> std::hex >> color)
	{
		outlineColor = Color(color);
	}

	return std::make_unique<Rectangle>(leftTop, rightBottom, fillColor, outlineColor);
}

std::unique_ptr<Triangle> ShapeParser::ParseTriangle(std::istream& input)
{
	Point a, b, c;
	Color fillColor = Color::White;
	Color outlineColor = Color::Transparent;

	input >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

	uint32_t color;
	if (input >> std::hex >> color)
	{
		fillColor = Color(color);
	}
	if (input >> std::hex >> color)
	{
		outlineColor = Color(color);
	}

	return std::make_unique<Triangle>(a, b, c, fillColor, outlineColor);
}
