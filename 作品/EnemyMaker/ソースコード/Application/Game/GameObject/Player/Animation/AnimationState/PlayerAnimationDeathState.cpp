#include "PlayerAnimationDeathState.h"


PlayerAnimationDeathState::PlayerAnimationDeathState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
	// 処理なし
}


PlayerAnimationDeathState::~PlayerAnimationDeathState()
{
	// 処理なし
}

void PlayerAnimationDeathState::Entry()
{
	PlayAnimationClip("Death", 1.0f, 0.3f);
}
