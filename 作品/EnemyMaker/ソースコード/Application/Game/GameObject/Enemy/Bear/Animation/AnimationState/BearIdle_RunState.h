/**
* @file BearIdle_RunState.h
* @brief BearIdle_RunStateクラスの定義
*/

#pragma once

//---------- 前方宣言 --------
#include "../../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

//----------- INCLUDES ----------
class CharacterMovementComponent;
class BlendAnimationClip;

/** 
* @class BearIdle_RunState
* @brief 熊の敵のIdleとRunのアニメーションステート 
*		 熊の敵の移動コンポーネントの速度の値を参照し現在の速度にあったアニメーションを再生する
*/
class BearIdle_RunState : public AnimationStateContext
{
public:	
	BearIdle_RunState(AnimationInstance* _animInstance);

private:
	/** 移動コンポーネント */
	std::weak_ptr<CharacterMovementComponent> mMoveComp;
		
	/** IdleとRunの閾値となる速度 */
	float mIdleToRunThresholdSpeed;

	/** 待機から走りへのアニメーション */
	std::weak_ptr<BlendAnimationClip> mIdleToWalk;

public:
	/**
	 * @fn　Entry
	 * @brief ステートの開始の処理
	 * @return void
	*/
	virtual void Entry();

	/**
	 * @fn　Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update();
};

