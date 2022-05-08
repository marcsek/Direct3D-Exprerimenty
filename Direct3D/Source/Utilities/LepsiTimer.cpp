#include "LepsiTimer.h"

LepsiTimer::LepsiTimer()
{
	last = std::chrono::steady_clock::now();
}

float LepsiTimer::Mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float LepsiTimer::Peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}


