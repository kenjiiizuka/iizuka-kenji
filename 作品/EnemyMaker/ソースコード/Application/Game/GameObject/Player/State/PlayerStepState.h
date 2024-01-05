/**
* @file PlayerStepState.h
* @brief PlayerStepStateクラスの定義
*/

#pragma once

//--------- INCLUDES --------
#include "PlayerStateContext.h"

/**
* @class PlayerStepState
* @brief プレイヤーのステップステート
*/
class PlayerStepState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	* 
	* @param Player* (_player)
	*/
	PlayerStepState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerStepState();

private:
	/** 初回のフレームかを判断する */
	bool mbFirstFrame;

public:
	/**
	* @fn Entry
	* @brief ステート開始処理
	*/
	void Entry() override;

	/**
	* @fn Update
	* @brief 更新処理
	*/
	void Update() override;

private:
	/**
	* @fn CheckAnimationEnd
	* @brief アニメーションが終了しているか確認する
	* @return bool true 終了 false 終了していない
	*/
	bool CheckAnimationEnd();

	/**
	* @fn CheckInputAble
	* @brief 入力可能なのかを判断する
	* @return bool true 入力可能 false 入力不可
	*/
	bool CheckInputAble() const;

};

