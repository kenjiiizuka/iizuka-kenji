#include "PlayerAnimationAttackState.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../Player.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../../../System/Logger/Logger.h"

using namespace PlayerData;

PlayerAnimationAttackState::PlayerAnimationAttackState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
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
	// mAnimationNames[AttackID_B4] = "B4";

	mAnimationBlendingTimes[AttackID_Y1] = 0.05f;
	mAnimationBlendingTimes[AttackID_Y2] = 0.05f;
	mAnimationBlendingTimes[AttackID_Y3] = 0.05f;
	mAnimationBlendingTimes[AttackID_B1] = 0.2f;
	mAnimationBlendingTimes[AttackID_B2] = 0.2f;
	mAnimationBlendingTimes[AttackID_B2_2] = 0.2f;
	mAnimationBlendingTimes[AttackID_B3] = 0.2f;
}

void PlayerAnimationAttackState::Entry(AttackID _entryState)
{
	mOldState = mState = _entryState;
	TransitionStateAndPlay<AttackID>
	(
		mState,
		_entryState,
		mAnimationNames[_entryState],
		1.0f,
		0.07f
	);

	// �v���C���[�̎擾
	mPlayer = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());

	Logger::GetInstance().WriteLog("Entry AttackAnimationState",1);
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
		PlayerAttack prevAttack = mPlayer->GetPrevAttack();
		PlayAnimationClip(playerAttack.mAnimationClipName, 1.0f, mPlayer->GetNextAttackInterpTime(), mPlayer->GetNextAttackInterpStartTime());
	}
	mOldState = mState;
}

bool PlayerAnimationAttackState::IsAttackEnd()
{
	return (mOwnerAnimationInstance->GetAnimationPlayer()->IsEndOnNextFrame() || !mOwnerAnimationInstance->GetAnimationPlayer()->IsPlay());
}


