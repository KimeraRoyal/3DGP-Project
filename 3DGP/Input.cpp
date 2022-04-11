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
	const bool alt = m_keyBinds.at(_bindingKey).HasAlt() && GetKeyDown(m_keyBinds.at(_bindingKey).GetAlt());
	return GetKeyDown(m_keyBinds.at(_bindingKey).GetValue()) || alt;
}

bool Input::GetBindingPressed(const size_t _bindingKey)
{
	KeyBinding& binding = m_keyBinds.at(_bindingKey);

	// First - was the main key pressed?
	bool pressed = GetKeyPressed(binding.GetValue());
	if(m_keyBinds.at(_bindingKey).HasAlt())
	{
		// If the main key was pressed, was the alt key down last frame?
		if (pressed) { pressed = pressed && !m_lastKeyMap.IsBitSet(binding.GetAlt()); }

		// If the main key was not pressed, was the alt key pressed this frame while the main key was unpressed last frame?
		else { pressed = GetKeyPressed(binding.GetAlt()) && !m_lastKeyMap.IsBitSet(binding.GetValue()); }
	}
	return pressed;
}

bool Input::GetBindingUnpressed(const size_t _bindingKey)
{
	KeyBinding& binding = m_keyBinds.at(_bindingKey);

	// First - was the main key unpressed?
	bool unpressed = GetKeyUnpressed(binding.GetValue());
	if (m_keyBinds.at(_bindingKey).HasAlt())
	{
		// If the main key was unpressed, is the alt key currently pressed?
		if (unpressed) { unpressed = unpressed && !GetKeyDown(binding.GetAlt()); }

		// If the main key was not unpressed, was the alt key unpressed this frame without the main key still being down?
		else { unpressed = GetKeyUnpressed(binding.GetAlt()) && !GetKeyDown(binding.GetValue()); }
	}
	return unpressed;
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
	return -GetBindingDown(_negativeKey) + GetBindingDown(_positiveKey);
}

int Input::GetTrinaryBindingPressed(const size_t _negativeKey, const size_t _positiveKey)
{
	return -GetBindingPressed(_negativeKey) + GetBindingPressed(_positiveKey);
}

int Input::GetTrinaryBindingUnpressed(const size_t _negativeKey, const size_t _positiveKey)
{
	return -GetBindingUnpressed(_negativeKey) + GetBindingUnpressed(_positiveKey);
}

int Input::GetAxisDown(const size_t _axisKey)
{
	InputAxis& axis = m_inputAxis.at(_axisKey);
	return GetTrinaryBindingDown(axis.GetNegative(), axis.GetPositive());
}

int Input::GetAxisPressed(const size_t _axisKey)
{
	InputAxis& axis = m_inputAxis.at(_axisKey);
	return GetTrinaryBindingPressed(axis.GetNegative(), axis.GetPositive());
}

int Input::GetAxisUnpressed(const size_t _axisKey)
{
	InputAxis& axis = m_inputAxis.at(_axisKey);
	return GetTrinaryBindingUnpressed(axis.GetNegative(), axis.GetPositive());
}

void Input::SetBinding(const std::string& _bindingName, const SDL_Scancode _keyCode, const SDL_Scancode _altKeyCode)
{
	const size_t key = std::hash<std::string>()(_bindingName);
	m_keyBinds.insert_or_assign(key, KeyBinding(_keyCode, _altKeyCode));
}

void Input::SetInputAxis(const std::string& _axisName, const std::string& _negative, const std::string& _positive)
{
	const size_t key = std::hash<std::string>()(_axisName);
	m_inputAxis.insert_or_assign(key, InputAxis(_negative, _positive));
}
