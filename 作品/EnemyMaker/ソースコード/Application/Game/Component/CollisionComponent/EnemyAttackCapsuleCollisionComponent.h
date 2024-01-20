/**
* @file EnemyAttackCapsuleCollisionComponent.h
* @brief EnemyAttackCapsuleCollisionComponentクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "CapsuleCollisionComponent.h"
#include "../../GameObject/CrossCharacterData.h"

/**
* @class EnemyAttackCapsuleCollisionComponent
* @brief 敵の攻撃用のカプセルの当たり判定
* @detail 攻撃対象に当たると自動でコリジョンがオフになり、オンにするまで当たり判定をとりません
*         ダメージとヒットリアクションを設定でき、プレイヤー側がそれを取得する
*/
class EnemyAttackCapsuleCollisionComponent : public CapsuleCollisionComponent
{
public:
	/**
	 * コンストラクタ
	*/
	EnemyAttackCapsuleCollisionComponent();

	/**
	* デストラクタ
	*/
	~EnemyAttackCapsuleCollisionComponent();

private:
	/** このコリジョンのダメージ */
	float mDamage;

	/** ヒットリアクション */
	CrossCharacter::HitReaction mHitReaction;

public:
	/**
	 * @fn　Init
	 * @brief 初期化処理
	 * @param float (_height) カプセルの高さ
	 * @param float (_radius) カプセルの半径
	 * @param float (_damage) ダメージ
	 * @return void
	*/
	void Init(float _height, float _radius, float _damage, CrossCharacter::HitReaction _hitReaction);
	
	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

public:	
	/**
	 * @fn　SetDamage
	 * @brief ダメージのセッター
	 * @param const float (_damage)
	 * @return void
	*/
	inline void SetDamage(const float _damage) noexcept;

	/**
	 * @fn　GetDamage
	 * @brief ダメージのゲッター
	 * @return float
	*/
	inline float GetDamage() const noexcept;

	/**
	 * @fn　GetHitReaction
	 * @brief ヒットリアクションのゲッター
	 * @return HitReaction ヒットリアクション
	*/
	inline CrossCharacter::HitReaction GetHitReaction() const noexcept;

	/**
	* @fn SetHitReaction
	* @brief ヒットリアクションのセッター
	* @param const CrossCharacter::HitReaction (_hitReaction)
	* @return void
	*/
	inline void SetHitReaction(const CrossCharacter::HitReaction _hitReaction) noexcept;
};

// --------------------- INLINES ---------------------------

inline void EnemyAttackCapsuleCollisionComponent::SetDamage(const float _damage) noexcept
{
	mDamage = _damage;
}

inline float EnemyAttackCapsuleCollisionComponent::GetDamage() const noexcept
{
	return mDamage;
}

inline CrossCharacter::HitReaction EnemyAttackCapsuleCollisionComponent::GetHitReaction() const noexcept
{
	return mHitReaction;
}

inline void EnemyAttackCapsuleCollisionComponent::SetHitReaction(const CrossCharacter::HitReaction _hitReaction) noexcept
{
	mHitReaction = _hitReaction;
}
