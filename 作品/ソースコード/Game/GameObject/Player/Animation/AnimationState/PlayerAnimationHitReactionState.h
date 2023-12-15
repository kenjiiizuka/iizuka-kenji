#pragma once
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"


/**
* @file  PlayerAnimationHitReactionState.h
* @brief プレイヤーのヒットリアクション状態
*/

class PlayerAnimationHitReactionState : public AnimationStateContext
{
public:
	PlayerAnimationHitReactionState() = delete;

	/**
	* 値の初期化
	*
	* @param[in] AnimationInstance* (_animInstance) このステートコンテキストを持つアニメーションインスタンス
	*/
	PlayerAnimationHitReactionState(AnimationInstance* _animInstance);

private:

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

