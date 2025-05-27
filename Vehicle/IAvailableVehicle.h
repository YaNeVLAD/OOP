#pragma once

#include "ICar.h"
#include "IPerson.h"
#include "IVehicle.h"

class IBus : public IVehicle<IPerson>
{
};

class IPoliceCar : public ICar<IPoliceMan>
{
};

class IRacingCar : public ICar<IRacer>
{
};

class ITaxi : public ICar<IPerson>
{
};
