#include "PlayerAnimationPulledState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../GameObject.h"
#include "../../../../Resource/BlendAnimationClip.h"
#include "../../../../GameObject/Player/Player.h"
#include "../../../../../Utility/MathLibrary.h"


PlayerAnimationPulledState::PlayerAnimationPulledState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mPlayerSpeed(0)
{
	mIdleToRun = std::static_pointer_cast<BlendAnimationClip>(mOwnerAnimationInstance->GetAnimationClipByName("PulledIdleToRun"));
}

void PlayerAnimationPulledState::Entry()
{		
	// ÉvÉåÉCÉÑÅ[ÇÃéÊìæ
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
	float speed = mMoveComp.lock()->GetCurrentVelocity().Length();
	mIdleToRun.lock()->InputBlendValue(speed);
}

