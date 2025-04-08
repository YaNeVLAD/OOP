#include "BaseShape.h"

#include <format>

std::string BaseShape::ToString() const
{
	return std::format(
		"  Area: {:.2f}\n"
		"  Perimeter: {:.2f}\n"
		"  Outline color: {:08X}\n",
		GetArea(),
		GetPerimeter(),
		GetOutlineColor().ToInt());
}

Color BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}
