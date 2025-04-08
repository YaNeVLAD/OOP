#pragma once

#include "BaseShape.h"

class BaseSolidShape : public BaseShape
{
public:
	BaseSolidShape() = default;

	explicit BaseSolidShape(Color fillColor, Color outlineColor);

	virtual ~BaseSolidShape() = default;

	Color GetFillColor() const;

	virtual std::string ToString() const override;

private:
	Color m_fillColor;
};
