#pragma once

#include "utility"

#include <type_traits>

namespace details
{

template <typename TValue>
class Allocator
{
	using TPointer = TValue*;

	static_assert(!std::is_const_v<TValue>, "The C++ Standard forbids containers of const elements "
											"because allocator<const T> is ill-formed.");
	static_assert(!std::is_function_v<TValue>, "The C++ Standard forbids allocators for function elements "
											   "because of [allocator.requirements].");
	static_assert(!std::is_reference_v<TValue>, "The C++ Standard forbids allocators for reference elements "
												"because of [allocator.requirements].");

public:
	TPointer Allocate(size_t size)
	{
		return static_cast<TPointer>(::operator new(CalculateBlockSize(size)));
	}

	void Free(TPointer block, size_t size)
	{
		if (block)
		{
			::operator delete(block, CalculateBlockSize(size));
		}
	}

	TPointer Reallocate(TPointer block, size_t oldSize, size_t newSize)
	{
		TPointer newBlock = Allocate(newSize);

		size_t copySize = oldSize < newSize ? oldSize : newSize;

		if constexpr (std::is_move_constructible_v<TValue>)
		{
			Move(newBlock, block, copySize);
		}
		else
		{
			Copy(newBlock, block, copySize);
		}

		Free(block, oldSize);

		return newBlock;
	}

private:
	void Move(TPointer dest, TPointer source, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			new (&dest[i]) TValue(std::move(source[i]));
			source[i].~TValue();
		}
	}

	void Copy(TPointer dest, TPointer source, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			new (&dest[i]) TValue(source[i]);
			source[i].~TValue();
		}
	}

	size_t CalculateBlockSize(size_t count)
	{
		return count * sizeof(TValue);
	}
};

} // namespace details
