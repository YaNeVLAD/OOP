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

	ConstListIterator(NodePtr node, const TList* list)
		: m_current(node)
		, m_list(list)
	{
	}

	reference operator*() const
	{
		assert(m_current != nullptr && "Cannot dereference a null iterator (likely end() or rend().base())");
		return m_current->data;
	}

	pointer operator->() const
	{
		assert(m_current != nullptr && "Cannot dereference a null iterator (likely end() or rend().base())");
		return &(m_current->data);
	}

	ConstListIterator& operator++()
	{
		assert(m_current != nullptr && "Cannot increment a null iterator (likely end())");
		if (m_current)
		{
			m_current = m_current->next;
		}
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
		assert(m_list != nullptr && "Iterator is not associated with a list.");
		if (m_current == nullptr)
		{
			m_current = m_list->m_tail;
		}
		else
		{
			m_current = m_current->prev;
		}

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
	const TList* m_list;

	friend class List<value_type>;
};

template <typename TList>
class ListIterator : public ConstListIterator<TList>
{
	using Base = ConstListIterator<TList>;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = typename TList::ValueType;
	using difference_type = std::ptrdiff_t;
	using pointer = typename TList::Pointer;
	using reference = value_type&;

	using NodePtr = typename TList::NodePtr;

	ListIterator(NodePtr node, const TList* list)
		: Base(node, list)
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
