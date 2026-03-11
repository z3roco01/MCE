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

#define KB_ACTION_JUMP VK_SPACE

#endif