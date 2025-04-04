#include "Utility.h"

#include "ISolidShape.h"
#include <algorithm>
#include <iomanip>

void PrintShapeInfo(std::ostream& output, const TShapePtr& shape)
{
	output << "Area: " << std::fixed << std::setprecision(3) << shape->GetArea() << std::endl;
	output << "Perimeter: " << std::fixed << std::setprecision(3) << shape->GetPerimeter() << std::endl;
	output << "Outline Color: " << std::hex << shape->GetOutlineColor() << std::endl;
	if (auto* it = dynamic_cast<const ISolidShape*>(shape.get()))
	{
		output << "Fill Color: " << std::hex << it->GetFillColor() << std::endl;
	}
	output << shape->ToString();
}

const TShapePtr& FindShapeWithMinPerimeter(const std::vector<TShapePtr>& shapes)
{
	auto lessPerimeter = [](const auto& a, const auto& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	};

	return *std::ranges::min_element(shapes, lessPerimeter);
}

const TShapePtr& FindShapeWithMaxArea(const std::vector<TShapePtr>& shapes)
{
	auto greaterArea = [](const auto& a, const auto& b) {
		return a->GetArea() < b->GetArea();
	};

	return *std::ranges::max_element(shapes, greaterArea);
}
