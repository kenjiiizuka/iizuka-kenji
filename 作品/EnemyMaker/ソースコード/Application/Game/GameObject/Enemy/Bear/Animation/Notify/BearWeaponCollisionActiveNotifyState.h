/**
* @file BearWeaponCollisionActiveNotifyState.h
* @brief BearWeaponCollisionActiveNotifyStateクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"
#include "../../../../CrossCharacterData.h"

//--------- 前方宣言 ----------
class EnemyAttackCapsuleCollisionComponent;

/**
* @class BearWeaponCollisionActiveNotifyState
* @brief 熊の敵の武器のコリジョンのActiveを切り替える通知ステート
*        熊の敵専用の通史ステートなので他のオブジェクトには使用できません
*/
class BearWeaponCollisionActiveNotifyState : public AnimationNotifyState
{
public:
	/**
	 * コンストラクタ
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param[in] float (_attachStartFrame) アタッチするフレームの開始
	 * @param[in] float (_attachEndFrame) アタッチするフレームの終了
	*/
	BearWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* デストラクタ
	*/
	~BearWeaponCollisionActiveNotifyState();

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

private:
	/** 熊の敵の武器のコリジョン */
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> mWeaponCollision;

	/** ダメージ */
	float mDamage;

	/** ヒットリアクション */
	CrossCharacter::HitReaction mHitReaction;

public:
	/**
	* @fn SetDamage
	* @brief コリジョンのダメージを設定する
	* @param const float _damage
	* @return void
	*/
	inline void SetDamage(const float _damage);

	/**
	* @fn SetHitReaction
	* @brief ヒットリアクションをセットする
	* @param const CrossCharacter::HitReaction (_hitReaction)
	* @return void
	*/
	inline void SetHitReaction(const CrossCharacter::HitReaction _hitReaction);
};

//---------- INLINES ----------

inline void BearWeaponCollisionActiveNotifyState::SetDamage(const float _damage)
{
	mDamage = _damage;
}

inline void BearWeaponCollisionActiveNotifyState::SetHitReaction(const CrossCharacter::HitReaction _hitReaction)
{
	mHitReaction = _hitReaction;
}
