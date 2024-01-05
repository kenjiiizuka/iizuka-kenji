//------------ INCLUDES -----------
#include "PlayerAnimationGuardState.h"
#include "../PlayerAnimationInstance.h"
#include "../../Player.h"

PlayerAnimationGuardState::PlayerAnimationGuardState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
	, mGuardState(GuardStart)
	, mPlayer(nullptr)
{
	// 処理なし
}

PlayerAnimationGuardState::~PlayerAnimationGuardState()
{
	// 処理なし
}

void PlayerAnimationGuardState::Entry()
{
	// ガード開始アニメーションを流す
	PlayAnimationClip("GuardStart", 1.1f);

	// プレイヤーを取得
	mPlayer = static_cast<Player*>(mOwnerAnimationInstance->GetOwner());
}

void PlayerAnimationGuardState::StateMachine()
{
	// アニメーションプレイヤーを取得
	std::shared_ptr<AnimationPlayer> animPlayer = mOwnerAnimationInstance->GetAnimationPlayer();

	switch (mGuardState)
	{
	case PlayerAnimationGuardState::GuardStart:
	{
		// 開始アニメーションの終了を検知
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
		// ガード終了アニメーションの終了を検知して遷移要求
		if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
		{
			mbNeedTransition = true;
		}
		break;
	}
	}
}

