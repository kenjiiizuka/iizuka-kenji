#include "BearWeaponCollisionActiveNotifyState.h"
#include "../../BearEnemy.h"
#include "../../../../../Resource/SkeletalMesh.h"
#include "../../../EnemyWeapon.h"
#include "../../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"

BearWeaponCollisionActiveNotifyState::BearWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// ˆ—‚È‚µ
}

BearWeaponCollisionActiveNotifyState::~BearWeaponCollisionActiveNotifyState()
{
	// ˆ—‚È‚µ
}

void BearWeaponCollisionActiveNotifyState::NotifyBegin()
{
	// ŒF‚Ì“G‚ğæ“¾
	 BearEnemy* enemy = dynamic_cast<BearEnemy*>(mSkeletalMesh.lock()->GetOwnerObject());
	 // ŒF‚Ì“G‚Å‚Í‚È‚©‚Á‚½‚çˆ—‚µ‚È‚¢
	 if (!enemy)
	 {
		 return;
	 }

	 // ŒF‚Ì“G‚Ì‚Á‚Ä‚¢‚é•Ší‚ÌƒRƒŠƒWƒ‡ƒ“‚ğæ“¾
	 mWeaponCollision = enemy->GetWeapon().lock()->GetAttackCollision();
	 mWeaponCollision.lock()->SetActiveCollision(true);
	 mWeaponCollision.lock()->SetDamage(mDamage);
	 mWeaponCollision.lock()->SetHitReaction(mHitReaction);
}

void BearWeaponCollisionActiveNotifyState::NotifyEnd()
{
	mWeaponCollision.lock()->SetActiveCollision(false);
	mWeaponCollision.lock()->SetDamage(0.0f); // ‘z’èŠO‚Èƒ_ƒ[ƒW‚ª”­¶‚µ‚È‚¢‚æ‚¤‚É0.0‚Éİ’è‚µ‚Ä‚¨‚­
}


