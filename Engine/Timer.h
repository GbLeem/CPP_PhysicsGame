#pragma once

#include <chrono> // for std::chrono functions

namespace gb
{
	class Timer
	{
	public:
		Timer()
			: mStartTime(clock_t::now())
		{}

		void reset();
		void start();
		void stop();
		double getElapsedMilli() const;
		double stopAndGetElapsedMilli();

	private:
		using clock_t = std::chrono::high_resolution_clock;

		std::chrono::time_point<clock_t> mStartTime;
		std::chrono::time_point<clock_t> mEndTime;
	};
}
