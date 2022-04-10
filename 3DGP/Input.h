#pragma once

#include <unordered_map>
#include <SDL2/SDL_events.h>

#include "BitSet.h"
#include "KeyBinding.h"

class Input
{
private:
	std::unordered_map<size_t, KeyBinding> m_keyBinds;
	
	BitSet m_keyMap;
	BitSet m_lastKeyMap;
public:
	void PostUpdate();
	
	void RegisterKeyboardInput(SDL_Event* _event);

	[[nodiscard]] bool GetKeyDown(SDL_Scancode _keyCode);
	[[nodiscard]] bool GetKeyPressed(SDL_Scancode _keyCode);
	[[nodiscard]] bool GetKeyUnpressed(SDL_Scancode _keyCode);

	[[nodiscard]] bool GetBindingDown(size_t _bindingKey);
	[[nodiscard]] bool GetBindingPressed(size_t _bindingKey);
	[[nodiscard]] bool GetBindingUnpressed(size_t _bindingKey);

	[[nodiscard]] int GetTrinaryKeyDown(SDL_Scancode _negative, SDL_Scancode _positive);
	[[nodiscard]] int GetTrinaryKeyPressed(SDL_Scancode _negative, SDL_Scancode _positive);
	[[nodiscard]] int GetTrinaryKeyUnpressed(SDL_Scancode _negative, SDL_Scancode _positive);

	[[nodiscard]] int GetTrinaryBindingDown(size_t _negativeKey, size_t _positiveKey);
	[[nodiscard]] int GetTrinaryBindingPressed(size_t _negativeKey, size_t _positiveKey);
	[[nodiscard]] int GetTrinaryBindingUnpressed(size_t _negativeKey, size_t _positiveKey);

	void SetBinding(const std::string& _bindingName, SDL_Scancode _keyCode, SDL_Scancode _altKeyCode);

	static size_t GetBindingKey(const std::string& _bindingName);
};

