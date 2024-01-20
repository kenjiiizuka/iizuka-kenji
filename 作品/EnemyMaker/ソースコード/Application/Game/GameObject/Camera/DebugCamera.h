/**
* @file DebugCamera.h
* @brief DebugCameraクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "Camera.h"

/**
* @class DebugCamera
* @brief デバッグ用の操作可能なカメラ キーボード操作
*/
class DebugCamera : public Camera
{
private:
	/**
	* @fn RotateMove
	* @brief 回転
	* @return void
	*/
	void RotateMove();

	/**
	* @fn Move 
	* @brief 移動
	* @return void
	*/
	void Move();

	/** 操作が有効なのか */
	bool bEnableInput = false;
public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;	
};

