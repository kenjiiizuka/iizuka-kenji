//----------- INCLUDES -----------
#include "EnemyAttackCapsuleCollisionComponent.h"
#include "../../../System/InputSystem/Input.h"

EnemyAttackCapsuleCollisionComponent::EnemyAttackCapsuleCollisionComponent()
    : mDamage(50.0f)
	, mHitReaction(CrossCharacter::HitReaction_Small)
{
	// 処理なし
}

EnemyAttackCapsuleCollisionComponent::~EnemyAttackCapsuleCollisionComponent()
{
	// 処理なし
}

void EnemyAttackCapsuleCollisionComponent::Init(float _height, float _radius, float _damage, CrossCharacter::HitReaction _hitReaction)
{
	CapsuleCollisionComponent::Init(_height, _radius);
	mDamage = _damage;
	mHitReaction = _hitReaction;
	mHitColor = { 1.0f, 0.0f, 1.0f, 1.0f };       // ヒットカラーは紫
	mDefaultColor = { 1.0f, 0.0f, 0.0f, 1.0f };   // デフォルトは赤

	// エネミーの攻撃チャンネルに設定
	SetCollisionChannel(Collision::Channel_EnemyAttack);

	// プレイヤーにたいしてオーバーラップに設定する
	SetCollisionTypes(Collision::Channel_Player, Collision::Type_Overlap);

	// 攻撃用コリジョンなので、基本的にはコリジョンはオフ
	SetActiveCollision(false);
}

void EnemyAttackCapsuleCollisionComponent::Update(const double _deltaTime)
{
	CapsuleCollisionComponent::Update(_deltaTime);

	// 一度でも当たっていたらコリジョンを切るようにする
	if (IsCurrentHit())
	{
		SetActiveCollision(false);
	}
}
