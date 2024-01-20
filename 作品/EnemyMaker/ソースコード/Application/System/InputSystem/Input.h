/**
* @file Input.h
* @brief Inputクラスの定義
*/

#pragma once

//------- INCLUDES ------
#include <Windows.h>

/**
* @fn Input
* @brief 入力クラス
* @detail キーボードの入力を管理するクラス
*/
class Input
{
private:
	/** 前フレームの入力情報 */
	static BYTE mOldKeyState[256];

	/** 今フレームの入力情報 */
	static BYTE mKeyState[256];
public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	static void Init();

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	static void Update();

	/**
	* @fn GetKeyPress
	* @brief 指定したキーが押下されているかを返す
	* @param BYTE (_keyCode)
	* @return bool true 押下されている false 押下されていない
	*/
	static bool GetKeyPress(BYTE _keyCode);

	/**
	* @fn GetKeyTrigger
	* @brief 指定したキーが押下（トリガー入力）されているかを返す
	* @param BYTE (_keyCode)
	* @return bool true 押下されている false 押下されていない
	*/
	static bool GetKeyTrigger(BYTE _keyCode);
};

