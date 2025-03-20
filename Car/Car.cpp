#include "Car.h"

#include <iostream>
#include <unordered_map>

const std::unordered_map<Car::Gear, std::pair<int, int>> m_gearSpeedLimits = {
	{ Car::Gear::Reverse, { 0, 20 } }, { Car::Gear::Neutral, { INT_MIN, INT_MAX } },
	{ Car::Gear::First, { 0, 30 } }, { Car::Gear::Second, { 20, 50 } },
	{ Car::Gear::Third, { 30, 60 } }, { Car::Gear::Fourth, { 40, 90 } },
	{ Car::Gear::Fifth, { 50, 150 } }
};

Car::Car()
{
}

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Car::Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

Car::Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_isEngineOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear != Gear::Neutral || m_speed != 0)
	{
		return false;
	}
	m_isEngineOn = false;
	return true;
}

bool Car::SetGear(Gear gear)
{
	if (gear < Gear::Reverse || gear > Gear::Fifth)
	{
		return false;
	}

	if (gear == Gear::Reverse && m_speed != 0)
	{
		return false;
	}

	if (!m_isEngineOn && gear != Gear::Neutral)
	{
		return false;
	}

	auto& [minSpeed, maxSpeed] = m_gearSpeedLimits.at(gear);
	if (m_speed < minSpeed || m_speed > maxSpeed)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetGear(int gear)
{
	return SetGear(static_cast<Gear>(gear));
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		return false;
	}
	if (!m_isEngineOn)
	{
		return false;
	}
	if (m_gear == Gear::Neutral && speed > m_speed)
	{
		return false;
	}

	auto& [minSpeed, maxSpeed] = m_gearSpeedLimits.at(m_gear);
	if (speed < minSpeed || speed > maxSpeed)
	{
		return false;
	}

	ChangeDirection(speed);

	m_speed = speed;

	return true;
}

void Car::ChangeDirection(int speed)
{
	bool isMovingBackward = (m_direction == Direction::Backward && m_gear == Gear::Neutral);

	if (speed == 0)
	{
		m_direction = Direction::Still;
	}
	else if (m_gear == Gear::Reverse || isMovingBackward)
	{
		m_direction = Direction::Backward;
	}
	else
	{
		m_direction = Direction::Forward;
	}
}
