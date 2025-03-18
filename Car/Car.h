#pragma once

#include <unordered_map>

class Car
{
public:
	enum class Gear
	{
		Reverse = -1,
		Neutral,
		First,
		Second,
		Third,
		Fourth,
		Fifth
	};

	enum class Direction
	{
		Still = 0,
		Forward,
		Backward
	};

	Car();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	std::unordered_map<Gear, std::pair<int, int>> m_gearSpeedLimits = {
		{ Gear::Reverse, { 0, 20 } }, { Gear::Neutral, { 0, 20 } }, { Gear::First, { 0, 30 } },
		{ Gear::Second, { 20, 50 } }, { Gear::Third, { 30, 60 } },
		{ Gear::Fourth, { 40, 90 } }, { Gear::Fifth, { 50, 150 } }
	};

	bool m_isEngineOn = false;
	Gear m_gear = Gear::Neutral;
	int m_speed = 0;
	Direction m_direction = Direction::Still;
};
