#pragma once

#include <SDL2/SDL_scancode.h>

struct KeyBinding
{
private:
	SDL_Scancode m_value;
	SDL_Scancode m_altValue;
public:
	KeyBinding(const SDL_Scancode _value, const SDL_Scancode _altValue)
		: m_value(_value), m_altValue(_altValue) {}

	[[nodiscard]] SDL_Scancode GetValue() const { return m_value; }
	[[nodiscard]] SDL_Scancode GetAlt() const { return m_altValue; }

	[[nodiscard]] bool HasAlt() const { return m_altValue; }
};
