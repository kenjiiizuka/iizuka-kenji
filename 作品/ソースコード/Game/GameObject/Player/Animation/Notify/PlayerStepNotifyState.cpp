#include "PlayerStepNotifyState.h"
#include "../../Player.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Component/CollisionComponent/CapsuleCollisionComponent.h"

PlayerStepNotifyState::PlayerStepNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// èàóùÇ»Çµ
}

PlayerStepNotifyState::~PlayerStepNotifyState()
{
	// èàóùÇ»Çµ
}

void PlayerStepNotifyState::NotifyBegin()
{
	Player* player = static_cast<Player*>(mSkeletalMesh.lock()->GetOwnerObject());
	mPlayerCollision = player->GetCollisionComponent();

	// ìGÇÃçUåÇÇ…ëŒÇµÇƒÇÃìñÇΩÇËîªíËÇñ≥å¯Ç…Ç∑ÇÈ
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_None);
}

void PlayerStepNotifyState::NotifyEnd()
{
	// ìGÇÃçUåÇÇ…ëŒÇ∑ÇÈìñÇΩÇËîªíËÇóLå¯Ç…Ç∑ÇÈ
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_Overlap);
}
