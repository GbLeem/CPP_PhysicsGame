#include "Timer.h"

namespace gb
{
	void Timer::reset()
	{
		mStartTime = clock_t::now();
	}

	void Timer::start()
	{
		reset();
	}

	void Timer::stop()
	{
		mEndTime = clock_t::now();
	}

	double Timer::getElapsedMilli() const
	{
		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(mEndTime - mStartTime).count();

		return static_cast<double>(elapsed);
	}

	double Timer::stopAndGetElapsedMilli()
	{
		stop();

		return getElapsedMilli();
	}

}
