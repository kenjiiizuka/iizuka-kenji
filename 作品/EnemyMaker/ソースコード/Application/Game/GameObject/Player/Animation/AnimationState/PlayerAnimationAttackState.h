﻿/**
* @file  PlayerAnimationAttackState.h
* @brief プレイヤーのアニメーションステート
*/

#pragma once

//--------- INCLUDES ---------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"
#include "../../PlayerData.h"
#include <array>

//--------- 前方宣言 ---------
class AnimationInstance;
class Player;

/**
* @class PlayerAnimationAttackState
* @brief プレイヤーの攻撃アニメーションステート
*/
class PlayerAnimationAttackState : public AnimationStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param[in] AnimationInstance (_animInstance) このステートを持つアニメーションインスタンス
	*/
	PlayerAnimationAttackState(AnimationInstance* _animInstance);


private:
	/** 現在している攻撃をステートとして持つ */
	PlayerData::AttackID mState;

	/** 前フレームにしていた攻撃 */
	PlayerData::AttackID mOldState;

	/** このステートで使うアニメーションの名前 */
	std::array<std::string, PlayerData::AttackID_Max> mAnimationNames;

	/** プレイヤー */
	Player* mPlayer;

public:
	/**
     * @fn　Entry
     * @brief このステートの開始の処理
     * @return void
    */
	void Entry(PlayerData::AttackID _entryState);

	/**
     * @fn　Update
     * @brief 更新処理 現在している攻撃と前回していた攻撃比べ変化があれば対応したアニメーションを再生する
     * @return void
    */
	void Update();

	/**
	 * @fn　IsAttackEnd
	 * @brief 攻撃アニメーションが完全に終了したことを返す
	 * @return bool 攻撃アニメーションが終了したか
	*/
	bool IsAttackEnd();
};

