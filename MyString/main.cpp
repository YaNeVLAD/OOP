#include "String.h"

#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using MilliSeconds = std::chrono::milliseconds;

template <class Function>
	requires std::is_invocable_v<Function>
auto RunWithTimer(const std::string& name, Function&& func)
{
	auto start = Clock::now();
	func();
	auto end = Clock::now();
	auto dur = std::chrono::duration_cast<MilliSeconds>(end - start);

	return dur.count();
}

int main()
{
	const size_t ATTEMPTS = 10;
	const size_t INNER_CYCLE_LEN = 1'000'000;
	std::vector<long long> times;
	times.reserve(ATTEMPTS);

	for (size_t i = 0; i < ATTEMPTS; ++i)
	{
		times.emplace_back(RunWithTimer("Appending to SLT String", []() {
			for (size_t i = 0; i < INNER_CYCLE_LEN; ++i)
			{
				std::string str1 = "1234567890123456789012345678901234567890123456789012345678901234567890";
				std::string str(str1);
			}
		}));
	}

	double sum = std::accumulate(times.begin(), times.end(), 0);
	double avg = sum / ATTEMPTS;

	std::cout << "////////////////////////////" << std::endl;
	std::cout << "Average Time: " << avg << "ms" << std::endl;
	std::cout << "////////////////////////////" << std::endl;

	times.clear();

	for (size_t i = 0; i < ATTEMPTS; ++i)
	{
		times.emplace_back(RunWithTimer("Appending to My String", []() {
			String str;
			for (size_t i = 0; i < INNER_CYCLE_LEN; ++i)
			{
				String str1 = "1234567890123456789012345678901234567890123456789012345678901234567890";
				String str(str1);
			}
		}));
	}

	sum = std::accumulate(times.begin(), times.end(), 0);
	avg = sum / ATTEMPTS;

	std::cout << "////////////////////////////" << std::endl;
	std::cout << "Average Time: " << avg << "ms" << std::endl;
	std::cout << "////////////////////////////" << std::endl;
}
