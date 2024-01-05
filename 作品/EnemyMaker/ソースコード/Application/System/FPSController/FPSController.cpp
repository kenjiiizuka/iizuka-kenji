//-------- INCLUDES ----------
#include "FPSController.h"
#include "../../ImGui/ImGuiUtility.h"
#include <thread>
#include <iostream>
#include <chrono>

//---------- 静的メンバ変数初期化 ---------
double   FPSController::mDeltaTime = 0;
double   FPSController::mFrameSeconds = 0;
double   FPSController::mLastTime{};
uint8_t FPSController::mTargetFPS = 60;

void FPSController::Init(const double _targetFPS)
{
	mTargetFPS = static_cast<uint8_t>(_targetFPS);
	mFrameSeconds = 1 / _targetFPS;
	mFrameSeconds = std::floor(mFrameSeconds * 1000) / 1000;
	mLastTime = timeGetTime() / 1000.0;
}

bool FPSController::StartFrame()
{	
	double currentTime = timeGetTime() / 1000.0; // 現在時刻の取得	
	// 前回フレームからの経過時間を取得
	double delta = (currentTime - mLastTime);	
	if (delta < mFrameSeconds)
	{
		return false;
	}	
	mDeltaTime = delta;	
	mLastTime = currentTime;
	return true;
}

void FPSController::onDebug()
{
	//デバッグ用処理
#if defined(DEBUG) || defined(_DEBUG)	

	static bool onfps = false;

	if (GetAsyncKeyState(VK_F1) & 0x08000) 
	{
		onfps = true;
	}
	if (onfps) 
	{
		ImGui::Begin("FPS Window");
		ImGui::Text("FPS : %.2f", 1.0 / mDeltaTime);
		ImGui::Text("DeltaTime : %f", mDeltaTime);
		ImGui::End();

		std::cout << mDeltaTime << std::endl;
		if (GetAsyncKeyState(VK_F1) & 0x08000 && GetAsyncKeyState(VK_SHIFT) & 0x08000) 
		{
			onfps = false;
		}
	}
#endif
}

void FPSController::Update()
{
	onDebug();
}
