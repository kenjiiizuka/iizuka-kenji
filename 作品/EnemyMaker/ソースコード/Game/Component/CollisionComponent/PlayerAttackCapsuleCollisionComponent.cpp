//---------- INCLUDES ------------
#include "PlayerAttackCapsuleCollisionComponent.h"
#include "../../GameObject/Player/Player.h"
#include <iostream>

PlayerAttackCapsuleCollisionComponent::PlayerAttackCapsuleCollisionComponent()
	: mDamage(0.0f)
{
	// �����Ȃ�
}

PlayerAttackCapsuleCollisionComponent::~PlayerAttackCapsuleCollisionComponent()
{
	// �����Ȃ�
}

void PlayerAttackCapsuleCollisionComponent::Init(const float _height, const float _radius, const float _damage)
{
	CapsuleCollisionComponent::Init(_height, _radius);
	mDamage = _damage;

	// �U���p�R���W�����Ȃ̂Ŕ�A�N�e�B�u
	SetActiveCollision(false);
}

void PlayerAttackCapsuleCollisionComponent::Update(const double _deltaTime)
{
	CapsuleCollisionComponent::Update(_deltaTime);

	// ��x�ł�������΃I�t�ɂ���
	if (IsCurrentHit())
	{
		SetActiveCollision(false);
	}
}

void PlayerAttackCapsuleCollisionComponent::ExecuteBeginHit()
{
	// ���ɂ��������Ă��Ȃ���Ώ������Ȃ�
	if(mBeginHitCollisions.size() <= 0)
	{
		return;
	}
	// �ŏ��ɓ����������̂�������BeginHit�����s����
	mOwner->BeginHit(mBeginHitCollisions[0]->GetOwner(), mBeginHitCollisions[0]);
}
