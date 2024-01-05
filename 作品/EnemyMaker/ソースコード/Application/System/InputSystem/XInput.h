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
	/** XInputState */
	static XINPUT_STATE mXInputState;

	/** パッドのボタン入力状況 */
	static std::array<bool, Pad::Max> mPadState;

	/** 前フレームのパッドボタンの入力状況 */
	static std::array<bool, Pad::Max> mOldPadState;

	/** パッドID */
	static std::array<WORD, Pad::Max> mPadID;

	/** コントローラーインデックス */
	static DWORD mControllerIndex;

	/** スティックが最大まで倒されたときの値 */
	static const float mMaxStickThumb; 
	
	/** 振動情報 */
	static XINPUT_VIBRATION mVibration;

	/** 振動しているかを示す */
	static bool mbVibration;

	/** 振動し初めてからの経過時間 */
	static float mElapsedVibrationTime;

	/** 振動する時間 */
	static float mVibrationTime;

public:
	/** 最大振動値 */
	static WORD mMaxVibration;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail XInputの初期化を行っている
	* @return void
	*/
	static void Init();

	/**
	* @fn Update
	* @brief 更新処理
	* @detail 入力状況を監視し、更新している
	* @return void
	*/
	static void Update();

private:
	/**
	 * @fn CheckPressedButtons
	 * @brief 現在のボタンの押下情報を確認し、更新する関数
	 * @return void
	*/
	static void CheckPressedPadButtons();

	/**
	* @fn VibrationUpdate
	* @brief 振動処理の更新
	* @return void
	*/
	static void VibrationUpdate();

public:
	/**
	* @fn Vibration
	* @brief コントローラー振動
	* @param const float (_vibrationTime) 振動する時間
	* @param const float (_leftMotorPower)
	* @param const float (_rightMotorPower)
	* @return void
	*/
	static void Vibration(const float _vibrationTime, const float _leftMotorPower, const float _rightMotorPower);

	/**
	 * @fn GetPadTrigger
	 * @brief 引数で指定したゲームパッドボタンのトリガー取得をする関数
	 * @return bool true 押された(押された瞬間) : false 押されていない（押された瞬間ではない）
	*/
	static bool GetPadTrigger(Pad _button);

	/**
	 * @fn GetPadPress
	 * @brief 引数で指定されたボタンが押されてるか取得する関数
	 * @return bool true 押されている : false 押されていない
	*/
	static bool GetPadPress(Pad _button);

	/**
	 * @fn GetPadRightStick
	 * @brief ゲームパッドの右スティックの倒れ具合を取得する
	 * @return Vector2 x,y軸の値を返す
	*/
	static DirectX::SimpleMath::Vector2 GetPadRightStick();

	/**
     * @fn GetPadLeftStick
     * @brief ゲームパッドの左スティックの倒れ具合を取得する
     * @return Vector2 x,y軸の値を返す
    */
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

	/**
	* @fn IsLeftStickInputAble
	* @brief 左スティックが入力があるかを返す
	* @return bool true 入力あり false 入力なし
	*/
	static bool IsLeftStickInputAble();
};
