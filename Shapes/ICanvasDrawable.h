#pragma once

#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(const ICanvas& canvas) = 0;
};
