#include "BaseSolidShape.h"

#include <format>

BaseSolidShape::BaseSolidShape(Color fillColor, Color outlineColor)
	: m_fillColor(fillColor)
	, BaseShape(outlineColor)
{
}

Color BaseSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string BaseSolidShape::ToString() const
{
	return std::format(
			   "  Fill color: {:08X}\n",
			   GetFillColor().ToInt())
		+ BaseShape::ToString();
}
