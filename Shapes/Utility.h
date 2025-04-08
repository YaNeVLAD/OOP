#pragma once
#include "BaseShape.h"
#include <memory>
#include <ostream>
#include <vector>

using ShapePtr = std::unique_ptr<BaseShape>;

void PrintShapeInfo(std::ostream& output, const ShapePtr& shape);
const ShapePtr& FindShapeWithMinPerimeter(const std::vector<ShapePtr>& shapes);
const ShapePtr& FindShapeWithMaxArea(const std::vector<ShapePtr>& shapes);
