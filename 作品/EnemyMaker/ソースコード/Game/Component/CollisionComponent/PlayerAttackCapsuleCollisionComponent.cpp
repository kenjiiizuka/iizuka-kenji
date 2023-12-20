//---------- INCLUDES ------------
#include "PlayerAttackCapsuleCollisionComponent.h"
#include "../../GameObject/Player/Player.h"
#include <iostream>

PlayerAttackCapsuleCollisionComponent::PlayerAttackCapsuleCollisionComponent()
	: mDamage(0.0f)
{
	// 処理なし
}

PlayerAttackCapsuleCollisionComponent::~PlayerAttackCapsuleCollisionComponent()
{
	// 処理なし
}

void PlayerAttackCapsuleCollisionComponent::Init(const float _height, const float _radius, const float _damage)
{
	CapsuleCollisionComponent::Init(_height, _radius);
	mDamage = _damage;

	// 攻撃用コリジョンなので非アクティブ
	SetActiveCollision(false);
}

void PlayerAttackCapsuleCollisionComponent::Update(const double _deltaTime)
{
	CapsuleCollisionComponent::Update(_deltaTime);

	// 一度でも当たればオフにする
	if (IsCurrentHit())
	{
		SetActiveCollision(false);
	}
}

void PlayerAttackCapsuleCollisionComponent::ExecuteBeginHit()
{
	// 何にも当たっていなければ処理しない
	if(mBeginHitCollisions.size() <= 0)
	{
		return;
	}
	// 最初に当たったものを引数にBeginHitを実行する
	mOwner->BeginHit(mBeginHitCollisions[0]->GetOwner(), mBeginHitCollisions[0]);
}
