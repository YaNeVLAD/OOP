#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual Color GetFillColor() const = 0;
};
