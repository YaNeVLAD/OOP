#pragma once

#include "CarImpl.hpp"
#include "IAvailableVehicle.h"
#include "VehicleImpl.hpp"

class Taxi : public CarImpl<VehicleImpl<ITaxi, IPerson>, IPerson>
{
public:
	Taxi(size_t placeCount, MakeOfTheCar makeOfCar)
		: CarImpl<VehicleImpl<ITaxi, IPerson>, IPerson>(placeCount, makeOfCar)
	{
	}
};

class PoliceCar : public CarImpl<VehicleImpl<IPoliceCar, IPoliceMan>, IPoliceMan>
{
public:
	PoliceCar(size_t placeCount, MakeOfTheCar makeOfCar)
		: CarImpl<VehicleImpl<IPoliceCar, IPoliceMan>, IPoliceMan>(placeCount, makeOfCar)
	{
	}
};

class RacingCar : public CarImpl<VehicleImpl<IRacingCar, IRacer>, IRacer>
{
public:
	RacingCar(size_t placeCount, MakeOfTheCar makeOfCar)
		: CarImpl<VehicleImpl<IRacingCar, IRacer>, IRacer>(placeCount, makeOfCar)
	{
	}
};

class Bus : public VehicleImpl<IBus, IPerson>
{
public:
	Bus(size_t placeCount)
		: VehicleImpl<IBus, IPerson>(placeCount)
	{
	}
};
