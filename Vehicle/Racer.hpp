#pragma once

#include "PersonImpl.hpp"

class Racer : public PersonImpl<IRacer>
{
public:
	Racer(const std::string& name, size_t awardsCount)
		: PersonImpl<IRacer>(name)
		, m_awardsCount(awardsCount)
	{
	}

	size_t GetAwardsCount() const override
	{
		return m_awardsCount;
	}

private:
	size_t m_awardsCount;
};
