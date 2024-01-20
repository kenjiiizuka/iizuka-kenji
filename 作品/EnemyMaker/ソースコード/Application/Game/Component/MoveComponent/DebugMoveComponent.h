/**
* @file DebugMoveComponent.h
* @brief DebugMoveComponentクラスの定義 
*/

#pragma once

//----------- INCLUDES -------------
#include "MoveComponent.h"

/**
* @class DebugMoveComponent
* @brief デバッグ移動用コンポーネント
*/
class DebugMoveComponent : public MoveComponent
{
private:
	/**
	* @fn Move
	* @brief 移動処理
	* @return void
	*/
	void Move();

	/**
	* @fn MoveRot
	* @brief 回転
	* @return void
	*/
	void MoveRot();

	/**
	* @fn MoveForward
	* @brief 前進処理
	* @param const float (_scaleValue) スケーリング値
	* @return void
	*/
	void MoveForward(const float _scaleValue) override;

	/**
	* @fn MoveRight
	* @brief 右移動処理
	* @param const float (_scaleValue) スケーリング値
	* @return void
	*/
	void MoveRight(const float _scaleValue) override;

	/**
	* @fn MoveUp
	* @brief 上移動処理
	* @param const float (_scaleValue) スケーリング値
	* @return void
	*/
	void MoveUp(const float _scaleValue) override;

public:
	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;
};

