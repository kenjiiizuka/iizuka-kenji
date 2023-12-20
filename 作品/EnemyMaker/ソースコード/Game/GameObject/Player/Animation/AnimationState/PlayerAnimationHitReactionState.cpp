#include "PlayerAnimationHitReactionState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../GameObject.h"
#include "../../../../Component/MoveComponent/CharacterMovementComponent.h"

PlayerAnimationHitReactionState::PlayerAnimationHitReactionState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
}

void PlayerAnimationHitReactionState::Entry(const std::string& _hitReaction)
{
	PlayAnimationClip(_hitReaction, AnimationInf::AnimationPlayType::PlayType_PositionSynchro);
}

void PlayerAnimationHitReactionState::Update()
{	
	std::shared_ptr<CharacterMovementComponent> moveComp = mOwnerAnimationInstance->GetOwner()->GetComponent<CharacterMovementComponent>();
	bNeedTransition = mOwnerAnimationInstance->GetAnimationPlayer()->IsEndOnNextFrame() || !mOwnerAnimationInstance->GetAnimationPlayer()->IsPlay();
}


