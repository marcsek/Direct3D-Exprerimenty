#pragma once

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template<typename T>
static T sq(T& x)
{
	return x * x;
}