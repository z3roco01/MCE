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

void KeyboardMouseInput::FrameEnd()
{
	// copy current state into previous
	memcpy_s(m_prevKeysDown, sizeof(m_prevKeysDown), m_keysDown, sizeof(m_keysDown));
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

bool KeyboardMouseInput::IsKeyJustPressed(UINT virtKey)
{
	if(virtKey >= 0x100) return false;
	// if the key was just pressed ( last frame was up )
	return m_keysDown[virtKey] && !m_prevKeysDown[virtKey];
}

bool KeyboardMouseInput::IsKeyJustReleased(UINT virtKey)
{
	if(virtKey >= 0x100) return false;
	// if the key was just release ( last frame was down )
	return !m_keysDown[virtKey] && m_prevKeysDown[virtKey];
}


void KeyboardMouseInput::m_ClearState()
{
	// set all keys and their previous state to up
	memset(m_keysDown, false, sizeof(m_keysDown));
	memset(m_prevKeysDown, false, sizeof(m_prevKeysDown));
}

#endif