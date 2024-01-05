#include "Input.h"

BYTE Input::mKeyState[256];
BYTE Input::mOldKeyState[256];

void Input::Init()
{
	memset(mOldKeyState, 0, 256);
	memset(mKeyState, 0, 256);
}

void Input::Update()
{
	memcpy(mOldKeyState, mKeyState, 256);
	GetKeyboardState(mKeyState);
}

bool Input::GetKeyPress(BYTE _keyCode)
{
	return (mKeyState[_keyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE _keyCode)
{
	return ((mKeyState[_keyCode] & 0x80) && !(mOldKeyState[_keyCode] & 0x80));
}
