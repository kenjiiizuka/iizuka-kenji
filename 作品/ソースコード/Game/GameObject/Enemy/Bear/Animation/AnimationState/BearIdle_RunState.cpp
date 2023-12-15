#include "BearIdle_RunState.h"
#include "../../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../GameObject.h"
#include "../../../../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../BearAnimationinstance.h"
#include "../../../../../Resource/BlendAnimationClip.h"
#include <iostream>

BearIdle_RunState::BearIdle_RunState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mIdleToRunThresholdSpeed(1.0f)
{
	 mIdleToWalk = std::static_pointer_cast<BlendAnimationClip>(mOwnerAnimationInstance->GetAnimationClipByName("IdleToRun"));
}

void BearIdle_RunState::Entry()
{
	mMoveComp = mOwnerAnimationInstance->GetOwner()->GetComponent<CharacterMovementComponent>();

	// 補間にかける時間を取得する
	float interpTime = static_cast<BearAnimationInstance*>(mOwnerAnimationInstance)->GetToIdleRunInterpTime();

	PlayAnimationClip("IdleToRun", 1.0f, interpTime, 0.0f);
	std::cout << " IdleRunState " << std::endl;
}

void BearIdle_RunState::Update()
{
	float speed = mMoveComp.lock()->GetCurrentVelocity().Length();
	mIdleToWalk.lock()->InputBlendValue(speed);
}

