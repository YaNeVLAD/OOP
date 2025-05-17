#pragma once

#include <algorithm>
#include <concepts>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMaxEx(const std::vector<T>& vec, T& maxValue, const Less& less = std::less<T>())
{
	static_assert(std::predicate<Less, const T&, const T&>,
		"Less type must match std::predicate concept. "
		"(Be invocable with two const T& and return bool)");

	if (auto maxIt = std::ranges::max_element(vec, less); maxIt != vec.end())
	{
		maxValue = *maxIt;
		return true;
	}

	return false;
}
