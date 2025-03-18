#include "Car.h"
#include <math.h>

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
	if (m_gear != Gear::Neutral && m_speed != 0)
	{
		return false;
	}
	else
	{
		m_isEngineOn = false;
		return true;
	}
}

bool Car::SetGear(Gear gear)
{
	if (gear < Gear::Reverse || gear > Gear::Fifth)
	{
		return false;
	}

	if (!m_isEngineOn && gear != Gear::Neutral)
	{
		return false;
	}

	auto& [minSpeed, maxSpeed] = m_gearSpeedLimits[gear];
	if (m_speed < minSpeed && m_speed > maxSpeed)
	{
		return false;
	}

	if (m_speed != 0 && gear == Gear::Reverse)
	{
		return false;
	}

	if ((m_gear == Gear::Reverse && m_direction == Direction::Backward) && m_speed != 0)
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
	auto& [minSpeed, maxSpeed] = m_gearSpeedLimits[m_gear];
	if (speed < minSpeed || speed > maxSpeed)
	{
		return false;
	}

	if (abs(speed) > abs(m_speed))
	{
		if (m_gear != Gear::Reverse)
		{
			m_direction = Direction::Forward;
		}

		if (m_gear == Gear::Reverse || m_gear == Gear::Neutral)
		{
			m_direction = Direction::Backward;
		}
	}

	if (speed == 0)
	{
		m_direction = Direction::Still;
	}

	m_speed = speed;
	return true;
}
