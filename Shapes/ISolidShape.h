#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
	virtual Color GetFillColor() const = 0;
};
