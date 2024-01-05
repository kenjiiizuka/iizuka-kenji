//------------- INCLUDES --------------
#include "PlayerHitReactionState.h"
#include "../Player.h"
#include "../Animation/PlayerAnimationInstance.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"


PlayerHitReactionState::PlayerHitReactionState(Player* _player)
	:PlayerStateContext(_player)
{
	// �����Ȃ�
}

PlayerHitReactionState::~PlayerHitReactionState()
{
	// �����Ȃ�
}

void PlayerHitReactionState::Entry()
{
	mbIsInputAble = false;
}

void PlayerHitReactionState::Update()
{
	// �A�j���[�V�������Đ�����Ă��邩���m�F����
	// �Đ�����Ă��Ȃ��A�I������ꍇ�͓��͉\�ɂ��ď����I��
	if (CheckAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	// �q�b�g���A�N�V�����A�j���[�V�����ɂ��Ă���ʒm������͉\���𔻒f����
	//	mbIsInputAble = CheckInputAble();
}

bool PlayerHitReactionState::CheckInputAble() const
{
	std::shared_ptr<AnimationInstance> animInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = animInstance->GetAnimationPlayer()->GetPlayAnimation().lock();
	return animClip->GetAnimnotifyState<PlayerInputAbleNotifyState>()->IsInputAble();	
}

bool PlayerHitReactionState::CheckAnimationEnd() const
{
	std::shared_ptr<AnimationInstance> animInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<AnimationPlayer> animPlayer = animInstance->GetAnimationPlayer();
	return  (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}
