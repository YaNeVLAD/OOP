#include <chrono>
#include <iostream>

class Timer
{
	using Clock = std::chrono::high_resolution_clock;

public:
	explicit Timer(std::string id)
		: m_name(std::move(id))
	{
	}

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	~Timer()
	{
		Stop();
	}

	double Stop()
	{
		if (!m_running)
		{
			return 0;
		}

		m_running = false;
		auto curr = Clock::now();
		auto dur = curr - m_start;
		std::cout << m_name << " took " << dur.count() << "ns"
				  << " (" << ToSeconds(dur) << "s)" << std::endl;

		return ToSeconds(dur);
	}

private:
	std::string m_name;
	bool m_running = true;
	Clock::time_point m_start = Clock::now();

	double ToSeconds(std::chrono::nanoseconds nanoseconds)
	{
		return std::chrono::duration<double>(nanoseconds).count();
	}
};
