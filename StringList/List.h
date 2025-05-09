#pragma once

#include <cassert>
#include <utility>

#include "Iteratable.hpp"
#include "ListItertator.h"

template <typename T>
class List : public details::Iteratable<List<T>, ListIterator<List<T>>, ConstListIterator<List<T>>>
{
	static_assert(std::is_object_v<T>, "The C++ Standard forbids containers of non-object types "
									   "because of [container.requirements].");

	struct Node
	{
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	using NodePtr = Node*;
	using IteratorBase = details::Iteratable<List<T>, ListIterator<List<T>>, ConstListIterator<List<T>>>;

public:
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;

	using Iterator = typename IteratorBase::Iterator;
	using ConstIterator = typename IteratorBase::ConstIterator;

	friend class ListIterator<List>;
	friend class ConstListIterator<List>;

	List();

	explicit List(std::size_t size);

	List(std::initializer_list<ValueType> initializerList);

	~List();

	List(const List& other);

	List& operator=(const List& other);

	List(List&& other) noexcept;

	List& operator=(List&& other) noexcept;

	void PushFront(const ValueType& value);

	template <typename... Args>
	void EmplaceFront(Args&&... args);

	void PushBack(const ValueType& value);

	template <typename... Args>
	void EmplaceBack(Args&&... args);

	void PopFront();

	void PopBack();

	Iterator Insert(ConstIterator where, ValueType&& value);

	Iterator Insert(ConstIterator where, const ValueType& value);

	Iterator Erase(ConstIterator where);

	bool Empty() const;

	std::size_t Size() const;

	void Clear();

	ValueType& Front();

	const ValueType& Front() const;

	ValueType& Back();

	const ValueType& Back() const;

	Iterator Begin();

	ConstIterator Begin() const;

	Iterator End();

	ConstIterator End() const;

private:
	Node* m_head;
	Node* m_tail;
	std::size_t m_size;

	void InsertFront(Node* node);

	void InsertBack(Node* node);

	Iterator InsertAt(ConstIterator where, Node* node);
};

template <typename T>
List<T>::List()
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
}

template <typename T>
List<T>::List(std::size_t size)
	: m_size(size)
{
	for (size_t i = 0; i < size; ++i)
	{
		EmplaceBack();
	}
}

template <typename T>
List<T>::List(std::initializer_list<ValueType> initializerList)
	: List()
{
	for (const auto& value : initializerList)
	{
		EmplaceBack(value);
	}
}

template <typename T>
List<T>::~List()
{
	Clear();
}

template <typename T>
List<T>::List(const List& other)
	: List()
{
	Node* current = other.m_head;
	while (current != nullptr)
	{
		EmplaceBack(current->data);
		current = current->next;
	}
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		List temp(other);
		std::exchange(m_head, temp.m_head);
		std::exchange(m_tail, temp.m_tail);
		std::exchange(m_size, temp.m_size);
	}

	return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept
	: m_head(std::exchange(other.m_head, nullptr))
	, m_tail(std::exchange(other.m_tail, nullptr))
	, m_size(std::exchange(other.m_size, 0))
{
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		m_head = std::exchange(other.m_head, nullptr);
		m_tail = std::exchange(other.m_tail, nullptr);
		m_size = std::exchange(other.m_size, 0);
	}

	return *this;
}

template <typename T>
void List<T>::PushFront(const ValueType& value)
{
	Node* newNode = new Node(value);
	InsertFront(newNode);
}

template <typename T>
void List<T>::PushBack(const ValueType& value)
{
	Node* newNode = new Node(value);
	InsertBack(newNode);
}

template <typename T>
void List<T>::PopFront()
{
	if (Empty())
	{
		return;
	}

	Node* temp = m_head;
	if (m_head == m_tail)
	{
		m_head = m_tail = nullptr;
	}
	else
	{
		m_head = m_head->next;
		m_head->prev = nullptr;
	}
	delete temp;
	m_size--;
}

template <typename T>
void List<T>::PopBack()
{
	if (Empty())
	{
		return;
	}

	Node* temp = m_tail;
	if (m_head == m_tail)
	{
		m_head = m_tail = nullptr;
	}
	else
	{
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
	}
	delete temp;
	m_size--;
}

template <typename T>
typename List<T>::Iterator List<T>::Insert(ConstIterator where, ValueType&& value)
{
	Node* newNode = new Node(std::forward<ValueType>(value));
	return InsertAt(where, newNode);
}

template <typename T>
typename List<T>::Iterator List<T>::Insert(ConstIterator where, const ValueType& value)
{
	Node* newNode = new Node(value);
	return InsertAt(where, newNode);
}

template <typename T>
typename List<T>::Iterator List<T>::Erase(ConstIterator where)
{
	if (Empty() || where == End())
	{
		return End();
	}

	Node* current = where.m_current;
	Iterator next(current->next, this);

	if (current == m_head)
	{
		PopFront();
	}
	else if (current == m_tail)
	{
		PopBack();
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete current;
		m_size--;
	}

	return next;
}

template <typename T>
bool List<T>::Empty() const
{
	return m_size == 0;
}

template <typename T>
std::size_t List<T>::Size() const
{
	return m_size;
}

template <typename T>
void List<T>::Clear()
{
	while (!Empty())
	{
		PopBack();
	}
}

template <typename T>
typename List<T>::ValueType& List<T>::Front()
{
	assert(!Empty() && "Calling Front() on an empty list");
	return m_head->data;
}

template <typename T>
const typename List<T>::ValueType& List<T>::Front() const
{
	return const_cast<List&>(*this).Front();
}

template <typename T>
typename List<T>::ValueType& List<T>::Back()
{
	assert(!Empty() && "Calling Back() on an empty list");
	return m_tail->data;
}

template <typename T>
const typename List<T>::ValueType& List<T>::Back() const
{
	return const_cast<List&>(*this).Back();
}

template <typename T>
typename List<T>::Iterator List<T>::Begin()
{
	return Iterator(m_head, this);
}

template <typename T>
typename List<T>::ConstIterator List<T>::Begin() const
{
	return ConstIterator(m_head, this);
}

template <typename T>
typename List<T>::Iterator List<T>::End()
{
	return Iterator(nullptr, this);
}

template <typename T>
typename List<T>::ConstIterator List<T>::End() const
{
	return ConstIterator(nullptr, this);
}

template <typename T>
void List<T>::InsertFront(Node* node)
{
	if (Empty())
	{
		m_head = m_tail = node;
	}
	else
	{
		node->next = m_head;
		m_head->prev = node;
		m_head = node;
	}
	node->prev = nullptr;
	m_size++;
}

template <typename T>
void List<T>::InsertBack(Node* node)
{
	if (Empty())
	{
		m_head = m_tail = node;
	}
	else
	{
		m_tail->next = node;
		node->prev = m_tail;
		m_tail = node;
	}
	node->next = nullptr;
	m_size++;
}

template <typename T>
typename List<T>::Iterator List<T>::InsertAt(ConstIterator where, Node* node)
{
	Node* current = where.m_current;

	if (current == m_head)
	{
		InsertFront(node);
		return Begin();
	}
	if (current == nullptr)
	{
		InsertBack(node);
		return End();
	}

	node->next = current;
	node->prev = current->prev;
	current->prev->next = node;
	current->prev = node;
	m_size++;
	return Iterator(node, this);
}

template <typename T>
template <typename... Args>
void List<T>::EmplaceFront(Args&&... args)
{
	Node* newNode = new Node(std::forward<Args>(args)...);
	InsertFront(newNode);
}

template <typename T>
template <typename... Args>
void List<T>::EmplaceBack(Args&&... args)
{
	Node* newNode = new Node(std::forward<Args>(args)...);
	InsertBack(newNode);
}
