#pragma once

#include <iterator>

namespace details
{

template <typename TContainer, typename TPointer, typename TConstPointer>
class Iteratable
{

private:
	TContainer* Ptr() { return static_cast<TContainer*>(this); }
	const TContainer* Ptr() const { return static_cast<const TContainer*>(this); }

public:
	using TIterator = TPointer;
	using TConstIterator = TConstPointer;

	using TReverseIterator = std::reverse_iterator<TIterator>;
	using TConstReverseIterator = std::reverse_iterator<TConstIterator>;

	TIterator begin() { return Ptr()->Begin(); }
	TIterator end() { return Ptr()->End(); }

	TConstIterator begin() const { return Ptr()->Begin(); }
	TConstIterator end() const { return Ptr()->End(); }

	TConstIterator cbegin() const { return begin(); }
	TConstIterator cend() const { return end(); }

	TReverseIterator rbegin() { return TReverseIterator(end()); }
	TReverseIterator rend() { return TReverseIterator(begin()); }

	TConstReverseIterator rbegin() const { return TConstReverseIterator(end()); }
	TConstReverseIterator rend() const { return TConstReverseIterator(begin()); }

	TConstReverseIterator crbegin() const { return rbegin(); }
	TConstReverseIterator crend() const { return rend(); }
};

} // namespace details
