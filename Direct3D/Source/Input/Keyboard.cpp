#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

void Keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}