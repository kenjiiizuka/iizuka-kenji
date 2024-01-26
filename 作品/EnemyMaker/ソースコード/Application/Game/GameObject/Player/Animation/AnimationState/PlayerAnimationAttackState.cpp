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
	// このステートでアニメーションの名前を紐づけ
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
	// プレイヤーの取得
	mPlayer = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());

	PlayerAttack playerAttack = mPlayer->GetCurrentAttack();
	mOldState = mState = playerAttack.mAttackID;


	if (mState == PlayerData::AttackID_Counter)
	{
		PlayAnimationClip(playerAttack.mAnimationClipName, 0.8f, 0.0f, 0.0f);
	}
	else
	{
		// アニメーションが全体敵に遅いので少し再生速度を上げて再生する
		PlayAnimationClip(playerAttack.mAnimationClipName, 1.2f, mPlayer->GetNextAttackInterpTime(), mPlayer->GetNextAttackInterpStartTime());
	}	
}

void PlayerAnimationAttackState::Update()
{
	PlayerAttack playerAttack = mPlayer->GetCurrentAttack();
	mState = playerAttack.mAttackID;

	// 攻撃していないなら何もしない
	if (mState == AttackID_NoAttack)
	{
		return;
	}

	// 別の攻撃に移っていたら対応したアニメーションを流す
	if (mOldState != mState && mOldState != AttackID_NoAttack)
	{	
		PlayAnimationClip(playerAttack.mAnimationClipName, 1.2f, mPlayer->GetNextAttackInterpTime(), mPlayer->GetNextAttackInterpStartTime());
	}
	mOldState = mState;
}

bool PlayerAnimationAttackState::IsAttackEnd()
{
	return (mOwnerAnimationInstance->GetAnimationPlayer()->IsEndOnNextFrame() || !mOwnerAnimationInstance->GetAnimationPlayer()->IsPlay());
}
