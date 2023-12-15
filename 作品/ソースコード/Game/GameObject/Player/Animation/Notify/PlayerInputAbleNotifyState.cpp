#include "PlayerInputAbleNotifyState.h"

PlayerInputAbleNotifyState::PlayerInputAbleNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
	, bInputAble(false)
{
	// èàóùÇ»Çµ
}

void PlayerInputAbleNotifyState::NotifyInit()
{
	bInputAble = false;
}

void PlayerInputAbleNotifyState::NotifyBegin()
{
	bInputAble = true;
}

void PlayerInputAbleNotifyState::NotifyEnd()
{
	bInputAble = false;
}


