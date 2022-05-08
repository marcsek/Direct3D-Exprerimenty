#pragma once
#include <chrono>

class LepsiTimer
{
public:
	LepsiTimer();
	float Mark();
	float Peek() const;

private:
	std::chrono::steady_clock::time_point last;

};

