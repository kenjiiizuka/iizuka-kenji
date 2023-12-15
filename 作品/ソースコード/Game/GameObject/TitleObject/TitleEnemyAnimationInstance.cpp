#include "TitleEnemyAnimationInstance.h"
#include "../../../Utility/MathLibrary.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"

TitleEnemyAnimationInstance::TitleEnemyAnimationInstance()
	: mBreathProbability(0.3f)
{
	// �����Ȃ�
}

TitleEnemyAnimationInstance::~TitleEnemyAnimationInstance()
{
	// �����Ȃ�
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
	// �A�j���[�V�������I��΃����_���Ńu���X�A�j���[�V�������Đ�����
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
