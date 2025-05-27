#pragma once

#include "ICar.h"

template <typename TBase, typename TPassenger>
	requires std::is_base_of_v<ICar<TPassenger>, TBase>
class CarImpl : public TBase
{
public:
	CarImpl(size_t placeCount, MakeOfTheCar makeOfCar)
		: TBase(placeCount)
		, m_makeOfCar(makeOfCar)
	{
	}

	MakeOfTheCar GetMakeOfTheCar() const override
	{
		return m_makeOfCar;
	}

private:
	MakeOfTheCar m_makeOfCar;
};
