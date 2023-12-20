#pragma once
#include <Windows.h>

class Input
{
private:
	static BYTE mOldKeyState[256];
	static BYTE mKeyState[256];
public:
	static void Init();
	static void Update();
	static bool GetKeyPress(BYTE _keyCode);
	static bool GetKeyTrigger(BYTE _keyCode);
};

