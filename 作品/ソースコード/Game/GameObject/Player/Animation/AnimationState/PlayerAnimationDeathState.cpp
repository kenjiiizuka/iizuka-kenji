#include "PlayerAnimationDeathState.h"


PlayerAnimationDeathState::PlayerAnimationDeathState(AnimationInstance* _animInstance)
	: AnimationStateContext(_animInstance)
{
	// �����Ȃ�
}


PlayerAnimationDeathState::~PlayerAnimationDeathState()
{
	// �����Ȃ�
}

void PlayerAnimationDeathState::Entry()
{
	PlayAnimationClip("Death", 1.0f, 0.3f);
}
