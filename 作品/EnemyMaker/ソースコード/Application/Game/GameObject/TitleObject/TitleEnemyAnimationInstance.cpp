#include "TitleEnemyAnimationInstance.h"
#include "../../../Utility/MathLibrary.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"

TitleEnemyAnimationInstance::TitleEnemyAnimationInstance()
	: mBreathProbability(0.3f)
{
	// 処理なし
}

TitleEnemyAnimationInstance::~TitleEnemyAnimationInstance()
{
	// 処理なし
}

void TitleEnemyAnimationInstance::AnimationInit()
{
	//LoadAnimationClip("assets/Enemy/Animation/IdleBreathing.fbx", "Breath");
	LoadAnimationClip("assets/Enemy/Animation/Idle.fbx", "Idle");

	mAnimationClips["Idle"]->SetLoop(true);

	PlayAnimationClip("Idle");
}

void TitleEnemyAnimationInstance::AnimationUpdate()
{
	// アニメーションが終ればランダムでブレスアニメーションを再生する
	if (mAnimPlayer.lock()->IsEndOnNextFrame())
	{
		/*if (mBreathProbability >= MathLibrary::RandomFloatInRange(0.0, 1.0f))
		{
			PlayAnimationClip("Breath");
		}
		else
		{
			PlayAnimationClip("Idle");
		}*/
	}
}
