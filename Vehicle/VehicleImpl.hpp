#pragma once

#include <vector>

#include "IVehicle.h"

template <typename TBase, typename TPassenger>
	requires std::is_base_of_v<IVehicle<TPassenger>, TBase>
class VehicleImpl : public TBase
{
public:
	VehicleImpl(size_t placeCount)
		: m_placeCount(placeCount)
	{
		m_passengers.reserve(placeCount);
	}

	bool IsEmpty() const override
	{
		return m_passengers.empty();
	}

	bool IsFull() const override
	{
		return m_passengers.size() >= m_placeCount;
	}

	size_t GetPlaceCount() const override
	{
		return m_placeCount;
	}

	size_t GetPassengerCount() const override
	{
		return m_passengers.size();
	}

	void RemoveAllPassenger() override
	{
		m_passengers.clear();
	}

	// @throw std::logic_error - when vehicle is full
	void AddPassenger(std::shared_ptr<TPassenger> passenger) override
	{
		if (IsFull())
		{
			throw std::logic_error("Vehicle is full. No place left for " + passenger->GetName());
		}
		m_passengers.push_back(passenger);
	}

	// @throw std::out_of_range - when index > GetPassengerCount()
	const TPassenger& GetPassenger(size_t index) const override
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("Index is out of range");
		}
		return *m_passengers[index];
	}

	// @throw std::out_of_range - when index > GetPassengerCount()
	void RemovePassenger(size_t index) override
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("Index is out of range");
		}
		m_passengers.erase(m_passengers.begin() + index);
	}

private:
	std::vector<std::shared_ptr<TPassenger>> m_passengers;
	size_t m_placeCount;
};
