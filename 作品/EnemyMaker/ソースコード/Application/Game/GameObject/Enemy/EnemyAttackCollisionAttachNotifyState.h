#pragma once
#include <string>
#include "../../Component/SkeletalMeshComponent/AnimationNotifyState.h"
#include "../CrossCharacterData.h"

/**
* @file  AnimationNotifyState.h
* @brief 指定されたボーンに指定されたフレーム間にカプセルコリジョンをアタッチするクラスの定義
*/

class EnemyAttackCapsuleCollisionComponent;

/** 敵の攻撃コリジョンを指定されたフレーム間アタッチする通知ステート */
class EnemyAttackCollisionAttachNotifyState : public AnimationNotifyState
{
public:
	/**
	 * 値の初期化
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param[in] uint16_t (_attachStartFrame) アタッチするフレームの開始
	 * @param[in] uint16_t (_attachEndFrame) アタッチするフレームの終了
	*/
	EnemyAttackCollisionAttachNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

private:
	/** 当たり判定 */
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> mCollision;

	/** 当たり判定をアタッチするボーンの名前 */
	std::string mAttachBoneName;

	/** 発生させた当たり判定のダメージ */
	float mDamage;

	/** カプセルの高さ */
	float mCapsuleHeight;

	/** カプセルの半径 */
	float mCapsuleRadius;

	/** ヒットリアクション */
	CrossCharacter::HitReaction mHitReaction;

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

	/**
	 * @fn　SetDamage
	 * @brief 当たり判定のダメージのセッター
	 * @param const float (_damage)
	 * @return void
	*/
	inline void SetDamage(const float _damage);

	/**
	 * @fn　SetAttachBoneName
	 * @brief アタッチするボーンの名前
	 * @param const std::string& (_attachBoneName)
	 * @return void
	*/
	inline void SetAttachBoneName(const std::string& _attacheBoneName);

	/**
	 * @fn　SetCapsuleHeight
	 * @brief カプセルの高さのセッター
	 * @param const float _height
	 * @return void
	*/
	inline void SetCapsuleHeight(const float _height);

	/**
	 * @fn　SetCasuleRadius
	 * @brief カプセルの半径のセッター
	 * @param const float (_radius)
	 * @return void
	*/
	inline void SetCapsuleRadius(const float _radius);

	/**
	* @fn GetAttackCollision
	* @brief 攻撃用コリジョンを返す
	* @return std::weak_ptr<EnemyAttackCapsuleCollisionComponent>
	*/
	inline std::weak_ptr<EnemyAttackCapsuleCollisionComponent> GetAttackCollision() const noexcept;

	/**
	* @fn SetHitReaction
	* @brief ヒットリアクションのセッター
	* @param const CrossCharacter::HitReaction (_hitReaction)
	* @return void
	*/
	inline void SetHitReaction(const CrossCharacter::HitReaction _hitReaction) noexcept;

};

//--------------- INLINES --------------------------

inline void EnemyAttackCollisionAttachNotifyState::SetDamage(const float _damage)
{
	mDamage = _damage;
}

inline void EnemyAttackCollisionAttachNotifyState::SetAttachBoneName(const std::string& _attacheBoneName)
{
	mAttachBoneName = _attacheBoneName;
}

inline void EnemyAttackCollisionAttachNotifyState::SetCapsuleHeight(const float _height)
{
	mCapsuleHeight = _height;
}

inline void EnemyAttackCollisionAttachNotifyState::SetCapsuleRadius(const float _radius)
{
	mCapsuleRadius = _radius;
}

inline std::weak_ptr<EnemyAttackCapsuleCollisionComponent> EnemyAttackCollisionAttachNotifyState::GetAttackCollision() const noexcept
{
	return mCollision;
}

inline void EnemyAttackCollisionAttachNotifyState::SetHitReaction(const CrossCharacter::HitReaction _hitReaction) noexcept
{
	mHitReaction = _hitReaction;
}



