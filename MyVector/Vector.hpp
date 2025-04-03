#pragma once

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "ContainerBase.hpp"
#include "Iteratable.hpp"

template <typename TValue>
class Vector
	: public details::ContainerBase<TValue>
	, public details::Iteratable<Vector<TValue>, TValue*, const TValue*>
{
	using Base = details::ContainerBase<TValue>;

public:
	Vector() = default;

	Vector(std::initializer_list<TValue> list)
		: Base()
	{
		this->Reserve(list.size());

		for (auto& value : list)
		{
			this->EmplaceBack(value);
		}
	}

	~Vector() = default;

	void PushBack(TValue&& value)
	{
		this->EmplaceBack(std::forward<TValue>(value));
	}

	void PushBack(const TValue& value)
	{
		this->EmplaceBack(value);
	}

	typename Base::TReference operator[](size_t index)
	{
		if (index >= this->Size())
		{
			throw std::out_of_range("Vector index is out of range");
		}

		return *(this->Begin() + index);
	}

	typename Base::TConstReference operator[](size_t index) const
	{
		return const_cast<Vector&>(*this)[index];
	}
};
