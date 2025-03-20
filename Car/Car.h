#pragma once

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
	bool m_isEngineOn = false;
	Gear m_gear = Gear::Neutral;
	int m_speed = 0;
	Direction m_direction = Direction::Still;

	void ChangeDirection(int speed);
};
