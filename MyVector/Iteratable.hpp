#pragma once

#include <iterator>

namespace details
{

template <typename TContainer, typename TIterator, typename TConstIterator>
class Iteratable
{
	TContainer* Ptr() { return static_cast<TContainer*>(this); }
	const TContainer* Ptr() const { return static_cast<const TContainer*>(this); }

public:
	using Iterator = TIterator;
	using ConstIterator = TConstIterator;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() { return Ptr()->Begin(); }
	Iterator end() { return Ptr()->End(); }

	ConstIterator begin() const { return Ptr()->Begin(); }
	ConstIterator end() const { return Ptr()->End(); }

	ConstIterator cbegin() const { return begin(); }
	ConstIterator cend() const { return end(); }

	ReverseIterator rbegin() { return ReverseIterator(end()); }
	ReverseIterator rend() { return ReverseIterator(begin()); }

	ConstReverseIterator rbegin() const { return ConstReverseIterator(end()); }
	ConstReverseIterator rend() const { return ConstReverseIterator(begin()); }

	ConstReverseIterator crbegin() const { return rbegin(); }
	ConstReverseIterator crend() const { return rend(); }
};

} // namespace details
