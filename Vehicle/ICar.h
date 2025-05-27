#pragma once

#include "IVehicle.h"

enum class MakeOfTheCar
{
	BMW,
	Mitsubishi,
	Ford,
	Mercedes,
	Toyota,
	KIA,
	Ferrari,
	Porshe,
	Lexus,
	Nissan,
	Infiniti,
};

template <typename TPassenger>
class ICar : public IVehicle<TPassenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};
