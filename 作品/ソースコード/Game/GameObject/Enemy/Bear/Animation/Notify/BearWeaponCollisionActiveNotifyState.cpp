#include "BearWeaponCollisionActiveNotifyState.h"
#include "../../BearEnemy.h"
#include "../../../../../Resource/SkeletalMesh.h"
#include "../../../EnemyWeapon.h"
#include "../../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"

BearWeaponCollisionActiveNotifyState::BearWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// �����Ȃ�
}

BearWeaponCollisionActiveNotifyState::~BearWeaponCollisionActiveNotifyState()
{
	// �����Ȃ�
}

void BearWeaponCollisionActiveNotifyState::NotifyBegin()
{
	// �F�̓G���擾
	 BearEnemy* enemy = dynamic_cast<BearEnemy*>(mSkeletalMesh.lock()->GetOwnerObject());
	 // �F�̓G�ł͂Ȃ������珈�����Ȃ�
	 if (!enemy)
	 {
		 return;
	 }

	 // �F�̓G�̎����Ă��镐��̃R���W�������擾
	 mWeaponCollision = enemy->GetWeapon().lock()->GetAttackCollision();
	 mWeaponCollision.lock()->SetActiveCollision(true);
	 mWeaponCollision.lock()->SetDamage(mDamage);
	 mWeaponCollision.lock()->SetHitReaction(mHitReaction);
}

void BearWeaponCollisionActiveNotifyState::NotifyEnd()
{
	mWeaponCollision.lock()->SetActiveCollision(false);
	mWeaponCollision.lock()->SetDamage(0.0f); // �z��O�ȃ_���[�W���������Ȃ��悤��0.0�ɐݒ肵�Ă���
}


