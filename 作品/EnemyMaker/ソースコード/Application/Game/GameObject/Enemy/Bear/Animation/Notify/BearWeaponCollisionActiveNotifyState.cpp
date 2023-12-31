//----------- INCLUDES ------------
#include "BearWeaponCollisionActiveNotifyState.h"
#include "../../BearEnemy.h"
#include "../../../../../Resource/SkeletalMesh.h"
#include "../../../EnemyWeapon.h"
#include "../../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"

BearWeaponCollisionActiveNotifyState::BearWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
	, mDamage(0.0f)
	, mHitReaction(CrossCharacter::HitReaction_Small)
{
	// 処理なし
}

BearWeaponCollisionActiveNotifyState::~BearWeaponCollisionActiveNotifyState()
{
	// 処理なし
}

void BearWeaponCollisionActiveNotifyState::NotifyBegin()
{
	// 熊の敵を取得
	 BearEnemy* enemy = dynamic_cast<BearEnemy*>(mSkeletalMesh.lock()->GetOwnerObject());
	 // 熊の敵ではなかったら処理しない
	 if (!enemy)
	 {
		 return;
	 }

	 // 熊の敵の持っている武器のコリジョンを取得
	 mWeaponCollision = enemy->GetWeapon().lock()->GetAttackCollision();
	 mWeaponCollision.lock()->SetActiveCollision(true);
	 mWeaponCollision.lock()->SetDamage(mDamage);
	 mWeaponCollision.lock()->SetHitReaction(mHitReaction);
}

void BearWeaponCollisionActiveNotifyState::NotifyEnd()
{
	mWeaponCollision.lock()->SetActiveCollision(false);
	mWeaponCollision.lock()->SetDamage(0.0f); // 想定外なダメージが発生しないように0.0に設定しておく
}


