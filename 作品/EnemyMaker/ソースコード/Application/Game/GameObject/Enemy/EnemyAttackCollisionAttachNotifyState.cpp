#include "EnemyAttackCollisionAttachNotifyState.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../GameObject.h"
#include "../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../Resource/Skeleton.h"


EnemyAttackCollisionAttachNotifyState::EnemyAttackCollisionAttachNotifyState(
	SkeletalMeshAnimationClip* _attachAnimation,
	uint16_t _attachStartFrame,
	uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
	, mCapsuleHeight(0)
	, mCapsuleRadius(0)
	, mDamage(0)
	, mHitReaction(CrossCharacter::HitReaction_Small)
{
}

void EnemyAttackCollisionAttachNotifyState::NotifyBegin()
{
	// スケルタルメッシュのオーナーのゲームオブジェクトに攻撃用のコリジョンコンポーネントを追加する
	GameObject* owner = mSkeletalMesh.lock()->GetOwnerObject();
	mCollision = owner->AddComponent<EnemyAttackCapsuleCollisionComponent>();

	mCollision.lock()->Init(mCapsuleHeight, mCapsuleRadius, mDamage, mHitReaction);

	// アタッチするボーンを取得する
	std::shared_ptr<Bone> attachBone = mSkeletalMesh.lock()->GetSkeleton().lock()->GetBoneByName(mAttachBoneName).lock();

	// ボーンにアタッチ
	mCollision.lock()->AttachBone(attachBone, mSkeletalMesh.lock());

	// コリジョンの設定をする
	CollisionTypes collisionTypes;
	collisionTypes[Collision::Channel_Player] = Collision::Type_Overlap;
	collisionTypes[Collision::Channel_Enemy] = Collision::Type_None;
	collisionTypes[Collision::Channel_EnemyAttack] = Collision::Type_None;
	collisionTypes[Collision::Channel_Movable] = Collision::Type_None;
	collisionTypes[Collision::Channel_Static] = Collision::Type_None;
	mCollision.lock()->SetCollisionTypes(collisionTypes);

	mCollision.lock()->SetActiveCollision(true);
}

void EnemyAttackCollisionAttachNotifyState::NotifyEnd()
{
	// コリジョンコンポーネントを破棄する
	if (mCollision.lock())
	{
		mCollision.lock()->Destroy();
	}
}

