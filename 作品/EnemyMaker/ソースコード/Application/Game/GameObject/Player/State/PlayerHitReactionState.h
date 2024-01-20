/**
* @file PlayerHitReactionState.h
* @brief PlayerHitReactionStateクラスの定義
*/
#pragma once

//----------- INCLUDES ----------
#include "PlayerStateContext.h"

/**
* @class PlayerHitReactionState
* @brief プレイヤーのヒットリアクションステート
*/
class PlayerHitReactionState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param Player* (_player)
	*/
	PlayerHitReactionState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerHitReactionState();

public:
	/**
	* @fn Entry
	* @brief ステートの開始処理
	* @return void
	*/
	void Entry() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update() override;

private:
	/**
	* @fn CheckAnimationEnd
	* @brief ヒットリアクションのアニメーションが終了しているかを確認する
	* @return true 終了している false 終了していない
	*/
	bool CheckAnimationEnd() const;

	/**
	* @fn CheckInputAble
	* @brief 入力可能かを確認する
	* @detail ヒットリアクションアニメーションについているPlayerInputAbleNotifyStateから入力可能かを受け取る
	* @return bool true 可能 false 不可能
	*/
	bool CheckInputAble() const;

};
