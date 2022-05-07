#pragma once
#include <bitset>

class Keyboard
{
	friend class Window;

public:
	Keyboard() = default;

	bool KeyIsPressed(unsigned char keycode) const noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void ClearState() noexcept;

	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;

	std::bitset<nKeys> keystates;
};

