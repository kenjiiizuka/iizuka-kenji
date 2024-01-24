#pragma once

#define _CRT_SECURE_NO_WARNINGS

//-------- INCLUDES ---------
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <locale.h>
#include <DirectXMath.h>
#include <WICTextureLoader.h>
#include <d3d11.h>

#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(pop)

#pragma comment (lib,"winmm.lib")

constexpr float SCREEN_WIDTH = 1280.0f;
constexpr float SCREEN_HEIGHT = 720.0f;