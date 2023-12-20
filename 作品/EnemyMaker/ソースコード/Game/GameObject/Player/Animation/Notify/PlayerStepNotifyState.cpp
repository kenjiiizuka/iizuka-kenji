#include "PlayerStepNotifyState.h"
#include "../../Player.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Component/CollisionComponent/CapsuleCollisionComponent.h"

PlayerStepNotifyState::PlayerStepNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
{
	// �����Ȃ�
}

PlayerStepNotifyState::~PlayerStepNotifyState()
{
	// �����Ȃ�
}

void PlayerStepNotifyState::NotifyBegin()
{
	Player* player = static_cast<Player*>(mSkeletalMesh.lock()->GetOwnerObject());
	mPlayerCollision = player->GetCollisionComponent();

	// �G�̍U���ɑ΂��Ă̓����蔻��𖳌��ɂ���
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_None);
}

void PlayerStepNotifyState::NotifyEnd()
{
	// �G�̍U���ɑ΂��铖���蔻���L���ɂ���
	mPlayerCollision.lock()->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_Overlap);
}
