#include "PlayerAnimationHitReactionState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../GameObject.h"
#include "../../../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../../../Resource/SkeletalMeshAnimationClip.h"
#include "../Notify/PlayerHitReactionBigNotifyState.h"
#include "../../Player.h"
PlayerAnimationHitReactionState::PlayerAnimationHitReactionState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
}

void PlayerAnimationHitReactionState::Entry(const std::string& _hitReaction)
{
	PlayAnimationClip(_hitReaction, 1.0f);

	std::shared_ptr<SkeletalMeshAnimationClip> playAnimation = mOwnerAnimationInstance->GetAnimationPlayer()->GetPlayAnimation().lock();
	std::shared_ptr<PlayerHitReactionBigNotifyState> notify = playAnimation->GetAnimnotifyState<PlayerHitReactionBigNotifyState>();
	if (notify)
	{
		Player* player = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());
		notify->SetBlowVector(player->GetBlowVector());
	}
}

void PlayerAnimationHitReactionState::Update()
{	
	std::shared_ptr<CharacterMovementComponent> moveComp = mOwnerAnimationInstance->GetOwner()->GetComponent<CharacterMovementComponent>();
	std::shared_ptr<AnimationPlayer> animPlayer = mOwnerAnimationInstance->GetAnimationPlayer();

	// アニメーションの再生が終れば遷移する
	if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
	{
		mbNeedTransition = true;
	}
}


