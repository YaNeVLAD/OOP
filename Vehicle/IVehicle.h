#pragma once

#include <memory>

#include "IBaseVehicle.h"

template <typename TPassenger>
	requires std::is_base_of_v<IPerson, TPassenger>
class IVehicle : public IBaseVehicle
{
public:
	virtual void AddPassenger(std::shared_ptr<TPassenger> passenger) = 0;

	virtual const TPassenger& GetPassenger(size_t index) const = 0;

	virtual void RemovePassenger(size_t index) = 0;
};
