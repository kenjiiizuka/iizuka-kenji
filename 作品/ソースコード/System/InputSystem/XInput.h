/**
* @file XInput
* @brief XInputクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include <Windows.h>
#include <Xinput.h>
#include <array>
#include <SimpleMath.h>
#include "InputData.h"

/**
* @class XInput
* @brief XInputによるコントローラー、キーボード、マウスの入力を管理するクラス
*        同時に対応できるコントローラーは一つのみ
*/
class XInput
{
private:
	static XINPUT_STATE mXInputState;
	static std::array<bool, Pad::Max> mPadState;
	static std::array<bool, Pad::Max> mOldPadState;
	static std::array<WORD, Pad::Max> mPadID;

	static DWORD mControllerIndex;

	static const float mMaxStickThumb; // スティックの倒された時の最大値
	
public:
	static void Init();
	static void Update();

private:
	static void CheckPressedPadButtons();

public:
	static bool GetPadTrigger(Pad _button);
	static bool GetPadPress(Pad _button);

	static DirectX::SimpleMath::Vector2 GetPadRightStick();
	static DirectX::SimpleMath::Vector2 GetPadLeftStick();

	/**
	* @fn GetPadLeftStickRotation
	* @brief 
	*/
	static DirectX::SimpleMath::Vector3 GetPadLeftStickRotation();

	/**
	* @fn GetPressAnyKey
	* @brief なにかボタンが押されているかを返す
	* @return bool true 押されている false 押されていない
	*/
	static bool GetPressAnyKey();

	static bool IsLeftStickInputAble();
};
