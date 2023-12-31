#include "PlayerStepNotifyState.h"
#include "../../Player.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Component/CollisionComponent/CapsuleCollisionComponent.h"

PlayerStepNotifyState::PlayerStepNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// 処理なし
}

PlayerStepNotifyState::~PlayerStepNotifyState()
{
	// 処理なし
}

void PlayerStepNotifyState::NotifyBegin()
{
	Player* player = static_cast<Player*>(mSkeletalMesh.lock()->GetOwnerObject());
	mPlayerCollision = player->GetCollisionComponent();

	// 敵の攻撃に対しての当たり判定を無効にする
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_None);
}

void PlayerStepNotifyState::NotifyEnd()
{
	// 敵の攻撃に対する当たり判定を有効にする
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_Overlap);
}
