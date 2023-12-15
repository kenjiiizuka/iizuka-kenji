/**
* @file  FPSController.h
* @brief FPSControllerクラスの定義をしている
*/


#pragma once

//---------- INCLUDES -----------
#include <chrono>
#include <iostream>
#include <Windows.h>


/**
* @class FPSController
* @brief FPSを制御する機能をもつクラス
*/
class FPSController
{
private:
	static double mTargetFPS;	                                                    // 目標のFPS
	static uint8_t mDefaultFPS;
	static double   mDeltaTime;                                                       // フレーム間の経過時間
	static double   mLastTime;   // 前回フレーム時間

public:
	static void Init(uint8_t _targetFPS) 
	{
		mDefaultFPS = _targetFPS;
		mTargetFPS = 1000 / _targetFPS;
		mLastTime = timeGetTime();
	}

	static void StartFrame() 
	{
		double currentTime = timeGetTime(); // 現在時刻の取得	
		// 前回フレームからの経過時間を取得
		double delta = currentTime - mLastTime;
		
		if (delta < mTargetFPS) 
		{
			uint8_t sleep = static_cast<uint8_t>(mTargetFPS - delta);	
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
			// 待機後の時刻更新
			currentTime = timeGetTime(); // 現在時刻の取得		
		}
		mDeltaTime = currentTime - mLastTime;
		mLastTime = currentTime;
		onDebug();
	}

	static double GetDeltaTime() 
	{
		double delta = mDeltaTime / 1000;

		// ブレークポイント使った時に経過時間がとてつもない値になりデバッグしづらいので
		// 0.016にする
#if defined(DEBUG) || defined(_DEBUG)
		if (delta > 1)
		{
			delta = 0.016;
		}
#endif
		return delta;
	}

	static uint64_t GetTargetFPS() 
	{
		return static_cast<uint64_t>(mTargetFPS);
	}

	static uint8_t GetDefaultFPS() 
	{
		return mDefaultFPS;
	}

	static void onDebug() {
		//デバッグ用処理
#if defined(DEBUG) || defined(_DEBUG)	
		static bool onfps = false;
		if (GetAsyncKeyState(VK_F1) & 0x08000) {
			onfps = true;
		}
		if (onfps) {
			std::cout << mDeltaTime / 1000.f << std::endl;
			if (GetAsyncKeyState(VK_F1) & 0x08000 && GetAsyncKeyState(VK_SHIFT) & 0x08000) {
				onfps = false;
			}
		}
#endif
	}
};

