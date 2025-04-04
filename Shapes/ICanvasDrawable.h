#pragma once

#include "ICanvas.h"

class ICanvasDrawable
{
	virtual void Draw(const ICanvas& canvas) = 0;
};
