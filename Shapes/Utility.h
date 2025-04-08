#pragma once
#include "BaseShape.h"
#include <memory>
#include <ostream>
#include <vector>

using TShapePtr = std::unique_ptr<BaseShape>;

void PrintShapeInfo(std::ostream& output, const TShapePtr& shape);
const TShapePtr& FindShapeWithMinPerimeter(const std::vector<TShapePtr>& shapes);
const TShapePtr& FindShapeWithMaxArea(const std::vector<TShapePtr>& shapes);
