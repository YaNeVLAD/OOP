#pragma once

#include <memory>
#include <type_traits>

namespace details
{

template <typename TValue>
class Allocator
{
	using Pointer = TValue*;

	static_assert(!std::is_const_v<TValue>, "The C++ Standard forbids containers of const elements "
											"because allocator<const T> is ill-formed.");
	static_assert(!std::is_function_v<TValue>, "The C++ Standard forbids allocators for function elements "
											   "because of [allocator.requirements].");
	static_assert(!std::is_reference_v<TValue>, "The C++ Standard forbids allocators for reference elements "
												"because of [allocator.requirements].");

public:
	[[nodiscard]] Pointer Allocate(size_t size)
	{
		return static_cast<Pointer>(::operator new(CalculateBlockSize(size)));
	}

	void Free(Pointer block, size_t size)
	{
		if (block)
		{
			::operator delete(block, CalculateBlockSize(size));
		}
	}

	[[nodiscard]] Pointer Reallocate(Pointer block, size_t oldSize, size_t newSize)
	{
		Pointer newBlock = Allocate(newSize);

		size_t copySize = oldSize < newSize ? oldSize : newSize;

		if constexpr (std::is_move_constructible_v<TValue>)
		{
			std::uninitialized_move_n(block, copySize, newBlock);
		}
		else
		{
			std::uninitialized_copy_n(block, copySize, newBlock);
		}

		std::destroy_n(block, oldSize);

		Free(block, oldSize);

		return newBlock;
	}

private:
	static size_t CalculateBlockSize(size_t count)
	{
		return count * sizeof(TValue);
	}
};

} // namespace details
