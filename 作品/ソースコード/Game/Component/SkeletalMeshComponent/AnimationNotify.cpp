//--------- INCLUDES ----------
#include "AnimationNotify.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"


AnimationNotify::AnimationNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame)
	: mAttachedAnimation(_attachAnimation)
	, mAttachedFrame(_attachFrame)
{
	mSkeletalMesh = _attachAnimation->GetSkeletalMesh();
}

void AnimationNotify::NotifyInitBase()
{
	NotifyInit();
}

void AnimationNotify::NotifyBeginBase()
{	
	NotifyBegin();	
}

void AnimationNotify::NotifyEndBase()
{
	NotifyEnd();
}
