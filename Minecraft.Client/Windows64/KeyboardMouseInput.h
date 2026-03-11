#pragma once

#ifdef _WINDOWS64

#include <windows.h>

class KeyboardMouseInput
{
public:
	void Init();
	void Tick();
	// called at the end of frame, copies current state into previous
	void FrameEnd();

	// called in WndProc in Windows64_Minecraft when key message sent
	void OnKeyDown(WPARAM virtKey);
	void OnKeyUp(WPARAM virtKey);

	bool IsKeyDown(UINT virtKey);
	bool IsKeyJustPressed(UINT virtKey);
	bool IsKeyJustReleased(UINT virtKey);

private:
	// the state of each key last tick, keeps track of realsed and pressed
	bool m_prevKeysDown[0x100];
	// hold states of every key
	bool m_keysDown[0x100];

	// resets back to default state
	void m_ClearState();
};

// missing virtual key definitions, they are just their ascii values
#define VK_0 '0'
#define VK_1 '1'
#define VK_2 '2'
#define VK_3 '3'
#define VK_4 '4'
#define VK_5 '5'
#define VK_6 '6'
#define VK_7 '7'
#define VK_8 '8'
#define VK_9 '9'
#define VK_A 'A'
#define VK_B 'B'
#define VK_C 'C'
#define VK_D 'D'
#define VK_E 'E'
#define VK_F 'F'
#define VK_G 'G'
#define VK_H 'H'
#define VK_I 'I'
#define VK_J 'J'
#define VK_K 'K'
#define VK_L 'L'
#define VK_M 'M'
#define VK_N 'N'
#define VK_O 'O'
#define VK_P 'P'
#define VK_Q 'Q'
#define VK_R 'R'
#define VK_S 'S'
#define VK_T 'T'
#define VK_U 'U'
#define VK_V 'V'
#define VK_W 'W'
#define VK_X 'X'
#define VK_Y 'Y'
#define VK_Z 'Z'

// globally accessibly input object
extern KeyboardMouseInput g_KMInput;

#endif