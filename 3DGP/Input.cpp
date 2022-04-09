#include "Input.h"

void Input::PostUpdate()
{
	m_lastKeyMap.CopyBits(m_keyMap);
}

void Input::RegisterKeyboardInput(SDL_Event* _event)
{
	if(_event->type == SDL_KEYDOWN)
	{
		m_keyMap.SetBit(_event->key.keysym.scancode);
	}
	else
	{
		m_keyMap.ClearBit(_event->key.keysym.scancode);
	}
}

bool Input::GetKeyDown(const SDL_Scancode _keyCode)
{
	return m_keyMap.IsBitSet(_keyCode);
}

bool Input::GetKeyPressed(const SDL_Scancode _keyCode)
{
	return GetKeyDown(_keyCode) && !m_lastKeyMap.IsBitSet(_keyCode);
}

bool Input::GetKeyUnpressed(const SDL_Scancode _keyCode)
{
	return !GetKeyDown(_keyCode) && m_lastKeyMap.IsBitSet(_keyCode);
}

bool Input::GetBindingDown(const size_t _bindingKey)
{
	return GetKeyDown(m_keyBinds.at(_bindingKey));
}

bool Input::GetBindingPressed(const size_t _bindingKey)
{
	return GetKeyPressed(m_keyBinds.at(_bindingKey));
}

bool Input::GetBindingUnpressed(const size_t _bindingKey)
{
	return GetKeyUnpressed(m_keyBinds.at(_bindingKey));
}

int Input::GetTrinaryKeyDown(const SDL_Scancode _negative, const SDL_Scancode _positive)
{
	return -GetKeyDown(_negative) + GetKeyDown(_positive);
}

int Input::GetTrinaryKeyPressed(const SDL_Scancode _negative, const SDL_Scancode _positive)
{
	return -GetKeyPressed(_negative) + GetKeyPressed(_positive);
}

int Input::GetTrinaryKeyUnpressed(const SDL_Scancode _negative, const SDL_Scancode _positive)
{
	return -GetKeyUnpressed(_negative) + GetKeyUnpressed(_positive);
}

int Input::GetTrinaryBindingDown(const size_t _negativeKey, const size_t _positiveKey)
{
	return GetTrinaryKeyDown(m_keyBinds.at(_negativeKey), m_keyBinds.at(_positiveKey));
}

int Input::GetTrinaryBindingPressed(const size_t _negativeKey, const size_t _positiveKey)
{
	return GetTrinaryKeyPressed(m_keyBinds.at(_negativeKey), m_keyBinds.at(_positiveKey));
}

int Input::GetTrinaryBindingUnpressed(const size_t _negativeKey, const size_t _positiveKey)
{
	return GetTrinaryKeyUnpressed(m_keyBinds.at(_negativeKey), m_keyBinds.at(_positiveKey));
}

void Input::SetBinding(const std::string& _bindingName, const SDL_Scancode _keyCode)
{
	const size_t key = std::hash<std::string>()(_bindingName);
	m_keyBinds[key] = _keyCode;
}

size_t Input::GetBindingKey(const std::string& _bindingName)
{
	return std::hash<std::string>()(_bindingName);
}
