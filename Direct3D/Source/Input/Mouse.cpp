#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x, y };
}

int Mouse::GetX() const noexcept
{
	return x;
}

int Mouse::GetY() const noexcept
{
	return y;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

void Mouse::OnMouseMove(int x, int y) noexcept
{
	Mouse::x = x;
	Mouse::y = y;
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}





