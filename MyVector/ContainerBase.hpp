#pragma once

#include "Allocator.hpp"
#include <memory>

namespace details
{

template <typename TValue>
class ContainerBase
{
	static_assert(std::is_object_v<TValue>, "The C++ Standard forbids containers of non-object types "
											"because of [container.requirements].");

	using Allocator = Allocator<TValue>;

public:
	using Pointer = TValue*;
	using ConstPointer = const TValue*;

	using Reference = TValue&;
	using ConstReference = const TValue&;

	ContainerBase() = default;

	ContainerBase(size_t size, TValue value);

	ContainerBase(const ContainerBase& other);

	ContainerBase(ContainerBase&& other) noexcept;

	ContainerBase& operator=(const ContainerBase& other);

	ContainerBase& operator=(ContainerBase&& other) noexcept;

	virtual ~ContainerBase();

	template <typename... Args>
	Reference EmplaceBack(Args&&... args);

	void Resize(size_t newSize);

	void Reserve(size_t newCapacity);

	void PopBack();

	void Clear();

	size_t Size() const;

	size_t Capacity() const;

	Pointer Begin();

	Pointer End();

	ConstPointer Begin() const;

	ConstPointer End() const;

protected:
	void EmplaceAllBack(ConstPointer first, size_t size);

private:
	virtual size_t CalculateGrowth(size_t newSize);

	Pointer m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;

	Allocator m_allocator;
};

template <typename TValue>
inline ContainerBase<TValue>::ContainerBase(size_t size, TValue value)
	: m_data(m_allocator.Allocate(size))
	, m_size(size)
	, m_capacity(size)
{
	for (size_t i = 0; i < m_size; ++i)
	{
		new (&m_data[i]) TValue(value);
	}
}

template <class TValue>
inline ContainerBase<TValue>::ContainerBase(const ContainerBase& other)
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
{
	m_data = m_allocator.Allocate(m_capacity);
	for (size_t i = 0; i < m_size; ++i)
	{
		new (&m_data[i]) TValue(other.m_data[i]);
	}
}

template <class TValue>
inline ContainerBase<TValue>::ContainerBase(ContainerBase&& other) noexcept
	: m_data(std::exchange(other.m_data, nullptr))
	, m_size(std::exchange(other.m_size, 0))
	, m_capacity(std::exchange(other.m_capacity, 0))
{
}

template <class TValue>
inline ContainerBase<TValue>& ContainerBase<TValue>::operator=(const ContainerBase& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_capacity > other.m_size)
	{
		Clear();
		std::uninitialized_copy_n(other.m_data, other.m_size, m_data);
		m_size = other.m_size;
	}
	else
	{
		ContainerBase temp(other);
		std::swap(m_data, temp.m_data);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);
	}

	return *this;
}

template <class TValue>
inline ContainerBase<TValue>& ContainerBase<TValue>::operator=(ContainerBase&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	m_data = std::exchange(other.m_data, nullptr);
	m_size = std::exchange(other.m_size, 0);
	m_capacity = std::exchange(other.m_capacity, 0);

	return *this;
}

template <class TValue>
inline ContainerBase<TValue>::~ContainerBase()
{
	Clear();
	m_allocator.Free(m_data, m_capacity);
}

template <typename TValue>
inline void ContainerBase<TValue>::EmplaceAllBack(ConstPointer first, size_t size)
{
	if (!first)
	{
		return;
	}

	size_t totalSize = m_size + size;
	if (totalSize >= m_capacity)
	{
		size_t growth = CalculateGrowth(totalSize);
		m_data = m_allocator.Reallocate(m_data, m_size, growth);
		m_capacity = growth;
	}

	std::uninitialized_copy_n(first, size, m_data + m_size);
	m_size = totalSize;
}

template <class TValue>
inline void ContainerBase<TValue>::Resize(size_t newSize)
{
	if (newSize > m_capacity)
	{
		size_t oldSize = m_size;
		m_data = m_allocator.Reallocate(m_data, oldSize, newSize);
		m_capacity = newSize;
	}

	if (newSize > m_size)
	{
		for (size_t i = m_size; i < newSize; ++i)
		{
			new (&m_data[i]) TValue();
		}
	}
	else
	{
		for (size_t i = newSize; i < m_size; ++i)
		{
			m_data[i].~TValue();
		}
	}

	m_size = newSize;
}

template <class TValue>
inline void ContainerBase<TValue>::Reserve(size_t newCapacity)
{
	if (newCapacity > m_capacity)
	{
		size_t oldCapacity = m_capacity;
		m_capacity = newCapacity;
		m_data = m_allocator.Reallocate(m_data, oldCapacity, newCapacity);
	}
}

template <class TValue>
inline void ContainerBase<TValue>::PopBack()
{
	if (m_size > 0)
	{
		m_data[--m_size].~TValue();
	}
}

template <class TValue>
inline void ContainerBase<TValue>::Clear()
{
	std::destroy_n(m_data, m_size);
	m_size = 0;
}

template <class TValue>
inline size_t ContainerBase<TValue>::Size() const
{
	return m_size;
}

template <class TValue>
inline size_t ContainerBase<TValue>::Capacity() const
{
	return m_capacity;
}

template <class TValue>
inline ContainerBase<TValue>::Pointer ContainerBase<TValue>::Begin()
{
	return m_data;
}

template <class TValue>
inline ContainerBase<TValue>::Pointer ContainerBase<TValue>::End()
{
	return m_data + m_size;
}

template <class TValue>
inline ContainerBase<TValue>::ConstPointer ContainerBase<TValue>::Begin() const
{
	return m_data;
}

template <class TValue>
inline ContainerBase<TValue>::ConstPointer ContainerBase<TValue>::End() const
{
	return m_data + m_size;
}

template <class TValue>
inline size_t ContainerBase<TValue>::CalculateGrowth(size_t newSize)
{
	size_t oldCapacity = m_capacity;

	if (oldCapacity == 0)
	{
		return newSize == 0 ? 2 : newSize;
	}

	size_t growth = oldCapacity * 2;

	if (growth < newSize)
	{
		return newSize;
	}

	return growth;
}

template <class TValue>
template <typename... Args>
inline ContainerBase<TValue>::Reference ContainerBase<TValue>::EmplaceBack(Args&&... args)
{
	if (m_size >= m_capacity)
	{
		size_t oldCapacity = m_capacity;
		m_capacity = CalculateGrowth(oldCapacity);
		m_data = m_allocator.Reallocate(m_data, oldCapacity, m_capacity);
	}

	new (&m_data[m_size]) TValue(std::forward<Args>(args)...);
	return m_data[m_size++];
}

} // namespace details
