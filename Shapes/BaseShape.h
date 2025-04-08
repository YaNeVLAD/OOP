#pragma once

#include "Color.h"
#include <string>

class BaseShape
{
public:
	BaseShape() = default;
	explicit BaseShape(Color outlineColor)
		: m_outlineColor(outlineColor)
	{
	}

	virtual ~BaseShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;

	virtual std::string ToString() const;

	Color GetOutlineColor() const;

private:
	Color m_outlineColor;
};
