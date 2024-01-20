/**
* @file  PlayerAnimationHitReactionState.h
* @brief プレイヤーのヒットリアクション状態
*/

#pragma once

//--------- INCLUDES ---------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

/**
* @class PlayerAnimationHitReactionState
* @brief プレイヤーのヒットリアクションアニメーションステート
*/
class PlayerAnimationHitReactionState : public AnimationStateContext
{
public:
	PlayerAnimationHitReactionState() = delete;

	/**
	* コンストラクタ
	*
	* @param AnimationInstance* (_animInstance) このステートコンテキストを持つアニメーションインスタンス
	*/
	PlayerAnimationHitReactionState(AnimationInstance* _animInstance);

public:
	/**
	 * @fn　Entry
	 * @brief ステートの開始の処理
	 * @param const std::string& (_hitReaction) ヒットリアクションのアニメーションの名前
	 * @return void
	*/
	void Entry(const std::string& _hitReaction);

	/**
	 * @fn　Update
	 * @brief 更新処理
	 * @return void
	*/
	void Update() override;
};

