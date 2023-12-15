#pragma once
#include "../../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"


/**
* @file  BearSwipingAnimNotifyState.h
* @brief 腕の薙ぎ払い攻撃の通知ステートクラスの定義 
*/

class EnemyAttackCapsuleCollisionComponent;

/** このアニメーション中に当たり判定を発生させるクラスです */
class BearSwipingAnimNotifyState : public AnimationNotifyState
{
public:
	/**
	 * 値の初期化
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param[in] uint16_t (_attachStartFrame) アタッチするフレームの開始
	 * @param[in] uint16_t (_attachEndFrame) アタッチするフレームの終了
	*/
	BearSwipingAnimNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

private:
	/** 当たり判定 */
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> mCollision;

public:
	/**
　　 * @fn　NotifyBegin
　　 * @brief 通知の開始処理
　　 * @return void
　　*/
	void NotifyBegin() override;

	/**
	 * @fn　NotifyEnd
	 * @brief 通知の終了処理
	 * @return void
	*/
	void NotifyEnd() override;
	
};

