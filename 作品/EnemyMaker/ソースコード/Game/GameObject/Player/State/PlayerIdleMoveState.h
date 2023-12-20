/**
* @file PlayerIdleMoveState.h
* @brief PlayerIdleMoveStateクラスの定義
*/
#pragma once

//--------- INCLUDES ----------
#include <memory>
#include "PlayerStateContext.h"

//--------- 前方宣言 ---------
class PlayerMovementComponent;


/**
* @class PlayerIdleMoveState
* @brief プレイヤーの待機移動ステート
*/
class PlayerIdleMoveState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param Player* (_player)
	*/
	PlayerIdleMoveState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerIdleMoveState();

private:
	/** プレイヤーのムーブコンポーネント */
	std::weak_ptr<PlayerMovementComponent> mMoveComp;

public:
	/**
	* @fn Entry
	* @brief ステート開始処理
	*/
	void Entry() override;

	/**
	* @fn Exit
	* @brief ステート終章処理
	* @return void
	*/
	void Exit() override;

	/**
	* @fn Update
	* @brief 更新処理
	*/
	void Update() override;

};

