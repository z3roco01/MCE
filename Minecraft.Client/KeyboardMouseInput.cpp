#include "stdafx.h"

#ifdef _WINDOWS64

#include "KeyboardMouseInput.h"

KeyboardMouseInput g_KMInput;

void KeyboardMouseInput::Init()
{
	m_ClearState();
}

void KeyboardMouseInput::Tick()
{
}

void KeyboardMouseInput::OnKeyDown(WPARAM virtKey)
{
	// ensure it doesnt get some bad value
	if(virtKey >= 0x100) return;

	// this key is now down
	m_keysDown[virtKey] = true;
}

void KeyboardMouseInput::OnKeyUp(WPARAM virtKey)
{
	// ensure it doesnt get some bad value
	if(virtKey >= 0x100) return;
	
	// this key is now #up
	m_keysDown[virtKey] = false;
}

bool KeyboardMouseInput::IsKeyDown(UINT virtKey) 
{
	// always return key is up if it is out of bounds
	if(virtKey >= 0x100) return false;

	return m_keysDown[virtKey];
}


void KeyboardMouseInput::m_ClearState()
{
	// set all keys to up
	memset(m_keysDown, false, sizeof(m_keysDown));
}

#endif