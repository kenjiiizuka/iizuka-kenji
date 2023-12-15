#include "PlayerAnimationDeathState.h"


PlayerAnimationDeathState::PlayerAnimationDeathState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
	// ˆ—‚È‚µ
}


PlayerAnimationDeathState::~PlayerAnimationDeathState()
{
	// ˆ—‚È‚µ
}

void PlayerAnimationDeathState::Entry()
{
	PlayAnimationClip("Death", 1.0f, 0.3f);
}
