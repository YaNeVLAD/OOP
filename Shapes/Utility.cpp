#include "Utility.h"

#include "BaseSolidShape.h"
#include <algorithm>
#include <iomanip>

void PrintShapeInfo(std::ostream& output, const ShapePtr& shape)
{
	if (!shape)
	{
		output << "Shape not found" << std::endl;
		return;
	}

	output << shape->ToString();
}

const ShapePtr& FindShapeWithMinPerimeter(const std::vector<ShapePtr>& shapes)
{
	if (shapes.empty())
	{
		return nullptr;
	}

	auto lessPerimeter = [](const auto& a, const auto& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	};

	return *std::ranges::min_element(shapes, lessPerimeter);
}

const ShapePtr& FindShapeWithMaxArea(const std::vector<ShapePtr>& shapes)
{
	if (shapes.empty())
	{
		return nullptr;
	}

	auto greaterArea = [](const auto& a, const auto& b) {
		return a->GetArea() < b->GetArea();
	};

	return *std::ranges::max_element(shapes, greaterArea);
}
