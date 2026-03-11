#pragma once

#ifdef _WINDOWS64

#include <Windows.h>
#include "KeyboardMouseInput.h"

// TODO: Make reassignable in game, for now is hardcoded
#define KB_MENU_OK VK_RETURN
#define KB_MENU_CANCEL VK_ESCAPE
#define KB_MENU_UP VK_UP
#define KB_MENU_DOWN VK_DOWN
#define KB_MENU_LEFT VK_LEFT
#define KB_MENU_RIGHT VK_RIGHT
#define KB_MENU_PAGEUP VK_PRIOR
#define KB_MENU_PAGEDOWN VK_NEXT
#define KB_MENU_PAUSEMENU VK_ESCAPE
#define KB_MENU_Y VK_E
#define KB_MENU_X VK_R
#define KB_MENU_RIGHT_SCROLL VK_X
#define KB_MENU_LEFT_SCROLL VK_Z

#define KB_ACTION_FORWARD VK_W
#define KB_ACTION_BACKWARD VK_S
#define KB_ACTION_LEFT VK_A
#define KB_ACTION_RIGHT VK_D
#define KB_ACTION_JUMP VK_SPACE

#endif