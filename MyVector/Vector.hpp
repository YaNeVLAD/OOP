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
		Base::Reserve(list.size());

		for (auto& value : list)
		{
			Base::EmplaceBack(value);
		}
	}

	~Vector() = default;

	void PushBack(TValue&& value)
	{
		Base::EmplaceBack(std::forward<TValue>(value));
	}

	void PushBack(const TValue& value)
	{
		Base::EmplaceBack(value);
	}

	typename Base::TReference operator[](size_t index)
	{
		if (index >= Base::Size())
		{
			throw std::out_of_range("Vector index is out of range");
		}

		return *(Base::Begin() + index);
	}

	typename Base::TConstReference operator[](size_t index) const
	{
		return const_cast<Vector&>(*this)[index];
	}

	bool operator==(const Vector& other) const
	{
		if (Base::Size() != other.Size())
		{
			return false;
		}

		for (size_t i = 0; i < Base::Size(); ++i)
		{
			if ((*this)[i] != other[i])
			{
				return false;
			}
		}

		return true;
	}
};
