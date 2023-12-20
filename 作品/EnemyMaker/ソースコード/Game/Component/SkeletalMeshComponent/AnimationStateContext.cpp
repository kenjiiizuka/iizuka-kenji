//----------- INCLUDES -----------
#include "AnimationStateContext.h"
#include "AnimationInstance.h"

AnimationStateContext::AnimationStateContext(AnimationInstance* _animInstance)
	: bNeedTransition(false)
	, mStateName("ContextState")
	, mOwnerAnimationInstance(_animInstance)
{
}

void AnimationStateContext::PlayAnimationClip(const std::string& _animationName, const float _playRate, const float _interpTime, const float _toInterpAnimationClipTime)
{
	mOwnerAnimationInstance->PlayAnimationClip(_animationName, _playRate, _interpTime, _toInterpAnimationClipTime);
}
