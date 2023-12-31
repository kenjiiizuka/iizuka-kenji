#include "PlayerAnimationPulledState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../GameObject.h"
#include "../../../../Resource/BlendAnimationClip.h"
#include "../../../../GameObject/Player/Player.h"


PlayerAnimationPulledState::PlayerAnimationPulledState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mPlayerSpeed(0)
{
	mIdleToRun = std::static_pointer_cast<BlendAnimationClip>(mOwnerAnimationInstance->GetAnimationClipByName("PulledIdleToRun"));
}

void PlayerAnimationPulledState::Entry()
{		
	// プレイヤーの取得
	Player* player = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());

	PlayAnimationClip
	(
		"PulledIdleToRun",
		1.0f,
		player->GetIdleRunInterpTime()
	);

	mMoveComp = mOwnerAnimationInstance->GetOwner()->GetComponent<PlayerMovementComponent>();
	mPlayerSpeed = mMoveComp.lock()->GetCurrentVelocity().Length();
}

void PlayerAnimationPulledState::Update()
{
	mIdleToRun.lock()->InputBlendValue(mMoveComp.lock()->GetCurrentVelocity().Length());
}

