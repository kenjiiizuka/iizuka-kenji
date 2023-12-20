#include "PlayerAnimationRollState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../Player/Player.h"
#include "../../../../Component/MoveComponent/CharacterMovementComponent.h"

PlayerAnimationRollState::PlayerAnimationRollState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
}

void PlayerAnimationRollState::Entry()
{	
	Player* player = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());

	// �X�e�b�v�A�j���[�V�����Đ�
	PlayAnimationClip(player->GetStepAnimationClipName(),
		1.0f,
		player->GetStepAnimationInterpTime(),
		player->GetStepAnimationInterpStartTime()
	);
}

void PlayerAnimationRollState::Update()
{
	bNeedTransition = mOwnerAnimationInstance->GetAnimationPlayer()->IsEndOnNextFrame() || !mOwnerAnimationInstance->GetAnimationPlayer()->IsPlay();
}
