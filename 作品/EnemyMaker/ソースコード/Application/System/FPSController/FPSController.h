/**
* @file  FPSController.h
* @brief FPSControllerクラスの定義をしている
*/

#pragma once

//---------- INCLUDES -----------
#include <Windows.h>
#include <stdint.h>


/**
* @class FPSController
* @brief FPSを制御する機能をもつクラス
*/
class FPSController
{
private:
	/** 1フレームの時間 */
	static double mFrameSeconds;	

	/** 目標のFPS*/
	static uint8_t mTargetFPS;

	/** デルタタイム */
	static double   mDeltaTime;  
	
	/** 前回フレームでの時間(マシンタイム) */
	static double   mLastTime;

public:

	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 目標のFPSの設定、1フレームにかける時間を求める
	* @param const double (_targetFPS) 目標のFPS
	* @return void
	*/
	static void Init(const double _targetFPS);

	/**
	* @fn StartFrame
	* @brief フレームの開始処理
	* @return bool true フレーム開始 false 処理待ち
	*/
	static bool StartFrame();
	
	/**
	* @fn onDebug
	* @brief デバッグ用のデルタタイム表示関数
	* @return void
	*/
	static void onDebug();

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	static void Update();

	/**
	* @fn GetDeltaTime
	* @brief デルタタイムを返す
	* @return void
	*/
	static double GetDeltaTime() noexcept;

	/**
	* @fn GetDeltaTimeFloat
	* @brief デルタタイムを返す(Float)
	* @return void
	*/
	static inline float GetDeltaTimeFloat() noexcept;

	/**
	* @fn GetTargetFPS
	* @brief 目標のFPSを返す
	* @return void
	*/
	static inline uint8_t GetTargetFPS() noexcept;

};

//----------- INLINES ------------

inline uint8_t FPSController::GetTargetFPS() noexcept
{	
	return mTargetFPS;	
}

inline double FPSController::GetDeltaTime() noexcept
{	
	double delta = mDeltaTime;

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

inline float FPSController::GetDeltaTimeFloat() noexcept
{
	float delta = static_cast<float>(mDeltaTime);

	// ブレークポイント使った時に経過時間がとてつもない値になりデバッグしづらいので
	// 0.016にする
#if defined(DEBUG) || defined(_DEBUG)
	if (delta > 1)
	{
		delta = 0.016f;
	}
#endif
	return delta;
}
