//----------- INCLUDES ---------
#include "AnimationNotifyState.h"

AnimationNotifyState::AnimationNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotify(_attachAnimation, _attachStartFrame)
	, mStartFrame(_attachStartFrame)
	, mEndFrame(_attachEndFrame)
{
}

