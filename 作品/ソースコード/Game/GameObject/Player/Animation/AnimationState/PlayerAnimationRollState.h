#pragma once
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

/**
* @file  PlayerAnimationRollState.h
* @brief プレイヤーのアニメーションの回避アニメーションのステートクラスの定義
*/


class PlayerAnimationRollState : public AnimationStateContext
{
public:
	PlayerAnimationRollState() = delete;

	/**
	* 値の初期化
	*
	* @param[in] AnimationInstance* (_animInstance) このステートコンテキストを持つアニメーションインスタンス
	*/
	PlayerAnimationRollState(AnimationInstance* _animInstance);

	/**
	 * @fn　Entry
	 * @brief ステートの開始の処理
	 * @return void
	*/
	void Entry() override;

	/**
	 * @fn　Update
	 * @brief 更新処理
	 * @return void
	*/
	void Update() override;
};

