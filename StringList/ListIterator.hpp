#pragma once

#include <iterator>

template <typename T>
class List;

template <typename TList>
class ConstListIterator
{
	using NodePtr = typename TList::NodePtr;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = typename TList::ValueType;
	using difference_type = std::ptrdiff_t;
	using pointer = typename TList::ConstPointer;
	using reference = const value_type&;

	explicit ConstListIterator(NodePtr node)
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

	ConstListIterator& operator++()
	{
		m_current = m_current->next;
		return *this;
	}

	ConstListIterator operator++(int)
	{
		ConstListIterator temp = *this;
		++(*this);
		return temp;
	}

	ConstListIterator& operator--()
	{
		m_current = m_current->prev;
		return *this;
	}

	ConstListIterator operator--(int)
	{
		ConstListIterator temp = *this;
		--(*this);
		return temp;
	}

#if (__cplusplus >= 202002L)
	bool operator==(const ConstListIterator& other) const = default;
	bool operator!=(const ConstListIterator& other) const = default;
#else
	bool operator==(const ConstListIterator& other) const
	{
		return m_current == other.m_current;
	}

	bool operator!=(const ConstListIterator& other) const
	{
		return m_current != other.m_current;
	}

#endif

private:
	NodePtr m_current;

	friend class List<value_type>;
};

template <typename TList>
class ListIterator : public ConstListIterator<TList>
{
	using Base = ConstListIterator<TList>;
	using NodePtr = typename TList::NodePtr;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = typename TList::ValueType;
	using difference_type = std::ptrdiff_t;
	using pointer = typename TList::Pointer;
	using reference = value_type&;

	explicit ListIterator(NodePtr node)
		: Base(node)
	{
	}

	reference operator*() const
	{
		return const_cast<reference>(Base::operator*());
	}

	pointer operator->() const
	{
		return const_cast<pointer>(Base::operator->());
	}

	ListIterator& operator++()
	{
		Base::operator++();
		return *this;
	}

	ListIterator operator++(int)
	{
		ListIterator temp = *this;
		Base::operator++();
		return temp;
	}

	ListIterator& operator--()
	{
		Base::operator--();
		return *this;
	}

	ListIterator operator--(int)
	{
		ListIterator temp = *this;
		Base::operator--();
		return temp;
	}
};
