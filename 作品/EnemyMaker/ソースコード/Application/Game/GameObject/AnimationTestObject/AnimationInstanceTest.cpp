//----------- INCLUDES ----------
#include "AnimationInstanceTest.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"

AnimationInstanceTest::AnimationInstanceTest()
{
	// ˆ—‚È‚µ
}

AnimationInstanceTest::~AnimationInstanceTest()
{
	// ˆ—‚È‚µ
}

void AnimationInstanceTest::AnimationInit()
{
	LoadAnimationClip("assets/Enemy/Animation/Idle.fbx", "Idle");
	LoadAnimationClip("assets/Enemy/Animation/Attack/2ChainAttack_StrongLow.fbx", "StrongAttack");
	LoadAnimationClip("assets/Enemy/Animation/Attack/JumpSlash.fbx", "JumpSlash");
	LoadAnimationClip("assets/Enemy/Animation/TurnLeft90.fbx", "TurnLeft");

	
	mAnimationClips["Idle"]->SetLoop(true);
	mAnimationClips["StrongAttack"]->SetSynchroPosition(true);
	mAnimationClips["TurnLeft"]->SetSynchroRotation(true);
	mAnimationClips["JumpSlash"]->SetSynchroPosition(true);

	PlayAnimationClip("Idle", 1.0f);
}

void AnimationInstanceTest::AnimationUpdate()
{	
	static bool playAnim = false;

	if (ImGui::Button("StrongAttack"))
	{
		PlayAnimationClip("StrongAttack", 1.0f, 0.3f);
		playAnim = true;
	}
	if (ImGui::Button("JumpSlash"))
	{
		PlayAnimationClip("JumpSlash", 1.0f, 0.3f);
		playAnim = true;
	}

	if (ImGui::Button("TurnLeft"))
	{
		PlayAnimationClip("TurnLeft", 1.0f, 0.3f);
		playAnim = true;
	}

	if (!playAnim)
	{
		return;
	}

	// if (mAnimPlayer.lock()->IsEndOnNextFrame())
	// {
	// 	playAnim = false;
	// 	PlayAnimationClip("JumpSlash", 1.0f, 0.5f);
	// }
}
