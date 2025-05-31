#pragma once

#include <initializer_list>
#include <stdexcept>

#include "ContainerBase.hpp"
#include "Iteratable.hpp"

template <typename TValue>
class Vector final
	: public details::ContainerBase<TValue>
	, public details::Iteratable<Vector<TValue>, TValue*, const TValue*>
{
	using Base = details::ContainerBase<TValue>;
	using IteratorBase = details::Iteratable<Vector<TValue>, TValue*, const TValue*>;

	using _Iter = IteratorBase::Iterator;

public:
	Vector() = default;

	Vector(size_t size)
		: Base(size, TValue())
	{
	}

	Vector(size_t size, TValue value)
		: Base(size, value)
	{
	}

	Vector(std::initializer_list<TValue> list)
		: Base()
	{
		Base::EmplaceAllBack(list.begin(), list.size());
	}

	void PushBack(const TValue& value)
	{
		Base::EmplaceBack(value);
	}

	void EmplaceRange(_Iter first, _Iter last)
	{
		for (auto it = first; it < last; ++it)
		{
			Base::EmplaceBack(*it);
		}
	}

	typename Base::Reference operator[](size_t index)
	{
		if (index >= Base::Size())
		{
			throw std::out_of_range("Vector index is out of range");
		}

		return *(Base::Begin() + index);
	}

	typename Base::ConstReference operator[](size_t index) const
	{
		return const_cast<Vector&>(*this)[index];
	}

	template <typename TOtherValue>
	Vector& operator=(const Vector<TOtherValue>& other)
	{
		if (static_cast<const void*>(this) == static_cast<const void*>(&other))
		{
			return *this;
		}

		Vector temp;

		try
		{
			temp.Resize(other.Size());

			for (size_t i = 0; i < temp.Size(); ++i)
			{
				temp[i] = static_cast<TValue>(other[i]);
			}
		}
		catch (const std::exception&)
		{
			throw std::runtime_error("An exception was thrown during type conversion");
		}

		*this = std::move(temp);

		return *this;
	}

	bool operator==(const Vector& other) const
	{
		if (Base::Size() != other.Size())
		{
			return false;
		}
		bool equals = true;
		for (size_t i = 0; i < Base::Size(); ++i)
		{
			equals = (*this)[i] == other[i];
		}

		return equals;
	}
};
