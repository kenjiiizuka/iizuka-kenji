//---------- INCLUDES ------------
#include "PlayerAnimationAttackState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../Player.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../../../System/Logger/Logger.h"

using namespace PlayerData;

PlayerAnimationAttackState::PlayerAnimationAttackState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mOldState()
	, mPlayer(nullptr)
	, mState()
{
	// ���̃X�e�[�g�ŃA�j���[�V�����̖��O��R�Â�
	mAnimationNames[AttackID_Y1] = "Y1";
	mAnimationNames[AttackID_Y2] = "Y2";
	mAnimationNames[AttackID_Y3] = "Y3";
	mAnimationNames[AttackID_Y4] = "Y4";
	mAnimationNames[AttackID_B1] = "B1";
	mAnimationNames[AttackID_B2] = "B2";
	mAnimationNames[AttackID_B2_2] = "B2_2";
	mAnimationNames[AttackID_B3] = "B3";
}

void PlayerAnimationAttackState::Entry(AttackID _entryState)
{
	// �v���C���[�̎擾
	mPlayer = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());

	PlayerAttack playerAttack = mPlayer->GetCurrentAttack();
	mOldState = mState = playerAttack.mAttackID;

	float playRate = 1.0f;
	if (mState == PlayerData::AttackID_Counter)
	{
		playRate = 0.9f;
	}

	PlayAnimationClip(playerAttack.mAnimationClipName, playRate, mPlayer->GetNextAttackInterpTime(), mPlayer->GetNextAttackInterpStartTime());
}

void PlayerAnimationAttackState::Update()
{
	PlayerAttack playerAttack = mPlayer->GetCurrentAttack();
	mState = playerAttack.mAttackID;

	// �U�����Ă��Ȃ��Ȃ牽�����Ȃ�
	if (mState == AttackID_NoAttack)
	{
		return;
	}

	// �ʂ̍U���Ɉڂ��Ă�����Ή������A�j���[�V�����𗬂�
	if (mOldState != mState && mOldState != AttackID_NoAttack)
	{	
		PlayAnimationClip(playerAttack.mAnimationClipName, 1.0f, mPlayer->GetNextAttackInterpTime(), mPlayer->GetNextAttackInterpStartTime());
	}
	mOldState = mState;
}

bool PlayerAnimationAttackState::IsAttackEnd()
{
	return (mOwnerAnimationInstance->GetAnimationPlayer()->IsEndOnNextFrame() || !mOwnerAnimationInstance->GetAnimationPlayer()->IsPlay());
}
