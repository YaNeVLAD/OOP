#pragma once

#include "PersonImpl.hpp"

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	PoliceMan(const std::string& name, const std::string& department)
		: PersonImpl<IPoliceMan>(name)
		, m_department(department)
	{
	}

	std::string GetDepartment() const override
	{
		return m_department;
	}

private:
	std::string m_department;
};
