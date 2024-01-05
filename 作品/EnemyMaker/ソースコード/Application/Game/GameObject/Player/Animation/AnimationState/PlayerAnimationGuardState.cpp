//------------ INCLUDES -----------
#include "PlayerAnimationGuardState.h"
#include "../PlayerAnimationInstance.h"
#include "../../Player.h"

PlayerAnimationGuardState::PlayerAnimationGuardState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mGuardState(GuardStart)
	, mPlayer(nullptr)
{
	// �����Ȃ�
}

PlayerAnimationGuardState::~PlayerAnimationGuardState()
{
	// �����Ȃ�
}

void PlayerAnimationGuardState::Entry()
{
	// �K�[�h�J�n�A�j���[�V�����𗬂�
	PlayAnimationClip("GuardStart", 1.1f);

	// �v���C���[���擾
	mPlayer = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());
}

void PlayerAnimationGuardState::StateMachine()
{
	// �A�j���[�V�����v���C���[���擾
	std::shared_ptr<AnimationPlayer> animPlayer = mOwnerAnimationInstance->GetAnimationPlayer();

	switch (mGuardState)
	{
	case PlayerAnimationGuardState::GuardStart:
	{
		// �J�n�A�j���[�V�����̏I�������m
		if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
		{
			PlayAnimationClip("Guarding", 1.0f);
			mGuardState = Guarding;
		}

		break;
	}
	case PlayerAnimationGuardState::Guarding:
	{	
		if (!mPlayer->GetGuardInput())
		{
			PlayAnimationClip("StopGuard", 1.0f);
			mGuardState = GuardEnd;
		}
		break;
	}
	case PlayerAnimationGuardState::GuardEnd:
	{
		// �K�[�h�I���A�j���[�V�����̏I�������m���đJ�ڗv��
		if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
		{
			mbNeedTransition = true;
		}
		break;
	}
	}
}

