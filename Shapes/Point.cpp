#include "Point.h"

#include <cmath>

double Point::DistanceTo(Point other) const
{
	return std::hypot(x - other.x, y - other.y);
}
