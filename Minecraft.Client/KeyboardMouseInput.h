#pragma once

#ifdef _WINDOWS64

#include <windows.h>

class KeyboardMouseInput
{
public:
	void Init();
	void Tick();

	// called in WndProc in Windows64_Minecraft when key message sent
	void OnKeyDown(WPARAM virtKey);
	void OnKeyUp(WPARAM virtKey);

	bool IsKeyDown(UINT virtKey);
private:
	// hold states of every key
	bool m_keysDown[0x100];

	// resets back to default state
	void m_ClearState();
};

// globally accessibly input object
extern KeyboardMouseInput g_KMInput;

#endif