#pragma once

#include "PersonImpl.hpp"

class Person : public PersonImpl<IPerson>
{
public:
	Person(const std::string& name)
		: PersonImpl<IPerson>(name)
	{
	}
};
