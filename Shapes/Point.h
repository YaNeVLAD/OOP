#pragma once

struct Point
{
	double x = 0;
	double y = 0;

	double DistanceTo(Point other) const;

	friend bool operator==(const Point& first, const Point& second) = default;
};
