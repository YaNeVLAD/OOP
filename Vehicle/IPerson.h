#pragma once

#include <string>

class IPerson
{
public:
	virtual std::string GetName() const = 0;
};

class IPoliceMan : public IPerson
{
public:
	virtual std::string GetDepartment() const = 0;
};

class IRacer : public IPerson
{
public:
	virtual size_t GetAwardsCount() const = 0;
};
