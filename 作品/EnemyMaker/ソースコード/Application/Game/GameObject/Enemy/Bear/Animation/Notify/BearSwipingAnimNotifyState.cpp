//-------------- INCLUDES -------------
#include "BearSwipingAnimNotifyState.h"
#include "../../../../../Resource/SkeletalMesh.h"
#include "../../../../GameObject.h"
#include "../../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"

BearSwipingAnimNotifyState::BearSwipingAnimNotifyState(
	SkeletalMeshAnimationClip* _attachAnimation, 
	uint16_t _attachStartFrame, 
	uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// 処理なし
}

void BearSwipingAnimNotifyState::NotifyBegin()
{
	GameObject* owner = mSkeletalMesh.lock()->GetOwnerObject();
	mCollision = owner->AddComponent<EnemyAttackCapsuleCollisionComponent>();
	mCollision.lock()->Init(3, 4, 30, CrossCharacter::HitReaction_Small);
	mCollision.lock()->SetCollisionChannel(Collision::Channel_EnemyAttack);
	mCollision.lock()->SetCollisionTypes(Collision::Channel_Player, Collision::Type_Overlap);
}

void BearSwipingAnimNotifyState::NotifyEnd()
{
	if (mCollision.lock())
	{
		mCollision.lock()->Destroy();
	}
	
}
