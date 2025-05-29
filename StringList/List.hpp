#pragma once

#include <cassert>
#include <utility>

#include "../MyVector/Iteratable.hpp"
#include "ListIterator.hpp"

template <typename T>
class List : public details::Iteratable<List<T>, ListIterator<List<T>>, ConstListIterator<List<T>>>
{
	static_assert(std::is_object_v<T>, "The C++ Standard forbids containers of non-object types "
									   "because of [container.requirements].");

	friend class ListIterator<List>;
	friend class ConstListIterator<List>;

	struct Node
	{
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	using NodePtr = Node*;

public:
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;

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
	Node* m_sentinel;
	Node* m_head;
	Node* m_tail;
	std::size_t m_size;

	void InsertFront(Node* node);

	void InsertBack(Node* node);

	Iterator InsertAt(ConstIterator where, Node* node);

	void InitSentinel();
	void DeleteAllNodes();
	void CopyFrom(const List& other);
};

template <typename T>
List<T>::List()
{
	InitSentinel();
}

template <typename T>
List<T>::List(std::size_t size)
	: List()
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
	DeleteAllNodes();
	delete m_sentinel;
}

template <typename T>
List<T>::List(const List& other)
{
	InitSentinel();
	CopyFrom(other);
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept
	: m_head(std::exchange(other.m_head, nullptr))
	, m_tail(std::exchange(other.m_tail, nullptr))
	, m_sentinel(std::exchange(other.m_sentinel, nullptr))
	, m_size(std::exchange(other.m_size, 0))
{
	other.InitSentinel();
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		delete m_sentinel;

		m_head = std::exchange(other.m_head, nullptr);
		m_tail = std::exchange(other.m_tail, nullptr);
		m_sentinel = std::exchange(other.m_sentinel, nullptr);
		m_size = std::exchange(other.m_size, 0);

		other.InitSentinel();
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

	Node* nodeToDelete = m_head;
	Node* newHead = nodeToDelete->next;

	m_sentinel->next = newHead;
	newHead->prev = m_sentinel;

	m_head = newHead;

	if (m_size == 1)
	{
		m_tail = m_sentinel;
	}

	delete nodeToDelete;
	m_size--;
}

template <typename T>
void List<T>::PopBack()
{
	if (Empty())
	{
		return;
	}

	Node* nodeToDelete = m_tail;
	Node* newTail = nodeToDelete->prev;

	m_sentinel->prev = newTail;
	newTail->next = m_sentinel;

	m_tail = newTail;

	if (m_size == 1)
	{
		m_head = m_sentinel;
	}

	delete nodeToDelete;
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

	Node* nodeToDelete = where.m_current;
	Node* prevNode = nodeToDelete->prev;
	Node* nextNode = nodeToDelete->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	if (nodeToDelete == m_head)
	{
		m_head = nextNode;
	}

	if (nodeToDelete == m_tail)
	{
		m_tail = prevNode;
	}

	delete nodeToDelete;
	m_size--;

	return Iterator(nextNode);
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
	DeleteAllNodes();
	InitSentinel();
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
	return Iterator(m_head);
}

template <typename T>
typename List<T>::ConstIterator List<T>::Begin() const
{
	return ConstIterator(m_head);
}

template <typename T>
typename List<T>::Iterator List<T>::End()
{
	return Iterator(m_sentinel);
}

template <typename T>
typename List<T>::ConstIterator List<T>::End() const
{
	return ConstIterator(m_sentinel);
}

template <typename T>
void List<T>::InsertFront(Node* node)
{
	node->next = m_head;
	node->prev = m_sentinel;
	m_head->prev = node;
	m_sentinel->next = node;

	m_head = node;

	if (Empty())
	{
		m_tail = node;
	}
	m_size++;
}

template <typename T>
void List<T>::InsertBack(Node* node)
{
	node->prev = m_tail;
	node->next = m_sentinel;
	m_tail->next = node;
	m_sentinel->prev = node;

	m_tail = node;

	if (Empty())
	{
		m_head = node;
	}
	m_size++;
}

template <typename T>
typename List<T>::Iterator List<T>::InsertAt(ConstIterator where, Node* node)
{
	Node* current = where.m_current;
	Node* prev = current->prev;

	node->prev = prev;
	node->next = current;
	prev->next = node;
	current->prev = node;

	if (current == m_head)
	{
		m_head = node;
	}

	if (prev == m_tail)
	{
		m_tail = node;
	}

	m_size++;

	return Iterator(node);
}

template <typename T>
void List<T>::InitSentinel()
{
	m_sentinel = new Node();
	m_sentinel->prev = m_sentinel;
	m_sentinel->next = m_sentinel;
	m_head = m_sentinel;
	m_tail = m_sentinel;
	m_size = 0;
}

template <typename T>
void List<T>::DeleteAllNodes()
{
	Node* current = m_head;
	while (current != m_sentinel)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template <typename T>
void List<T>::CopyFrom(const List& other)
{
	Node* current = other.m_head;
	while (current != other.m_sentinel)
	{
		EmplaceBack(current->data);
		current = current->next;
	}
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
