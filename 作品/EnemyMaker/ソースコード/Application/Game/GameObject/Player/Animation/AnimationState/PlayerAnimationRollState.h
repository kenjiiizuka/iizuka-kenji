/**
* @file  PlayerAnimationRollState.h
* @brief プレイヤーのアニメーションの回避アニメーションのステートクラスの定義
*/

#pragma once

//-------- INCLUDES ---------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

/**
* @class PlayerAnimationRollState
* @brief プレイヤーの回避アニメーションステート
*/
class PlayerAnimationRollState : public AnimationStateContext
{
public:	
	/**
	* コンストラクタ
	*
	* @param AnimationInstance* (_animInstance) このステートコンテキストを持つアニメーションインスタンス
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

