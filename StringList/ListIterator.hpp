#pragma once

#include <iterator>

#include <variant>

template <typename T>
class List;

template <bool IsConst, class TList>
class BaseListIterator
{
	using NodePtr = typename TList::Node*;
	using ValueType = typename TList::ValueType;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::conditional_t<IsConst, const ValueType, ValueType>;
	using difference_type = std::ptrdiff_t;
	using pointer = std::add_pointer_t<value_type>;
	using reference = std::add_lvalue_reference_t<value_type>;

	explicit BaseListIterator(NodePtr node)
		: m_current(node)
	{
	}

	reference operator*() const
	{
		return m_current->data;
	}

	pointer operator->() const
	{
		return &(m_current->data);
	}

	BaseListIterator& operator++()
	{
		m_current = m_current->next;
		return *this;
	}

	BaseListIterator operator++(int)
	{
		BaseListIterator temp = *this;
		++(*this);
		return temp;
	}

	BaseListIterator& operator--()
	{
		m_current = m_current->prev;
		return *this;
	}

	BaseListIterator operator--(int)
	{
		BaseListIterator temp = *this;
		--(*this);
		return temp;
	}

#if (__cplusplus >= 202002L)
	bool operator==(const BaseListIterator& other) const = default;
	bool operator!=(const BaseListIterator& other) const = default;
#else
	bool operator==(const BaseListIterator& other) const
	{
		return m_current == other.m_current;
	}

	bool operator!=(const BaseListIterator& other) const
	{
		return m_current != other.m_current;
	}

#endif

private:
	NodePtr m_current;

	friend class List<ValueType>;
};

template <class TList>
using ListIterator = BaseListIterator<false, TList>;

template <class TList>
using ConstListIterator = BaseListIterator<true, TList>;
