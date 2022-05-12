#pragma once
#include <utility>

class Mouse
{
	friend class Window;

public:
	Mouse() = default;

	std::pair<int, int> GetPos() const noexcept;
	int GetX() const noexcept;
	int GetY() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	bool IsInWindow() const noexcept;

private:
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;

	int x, y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
};

