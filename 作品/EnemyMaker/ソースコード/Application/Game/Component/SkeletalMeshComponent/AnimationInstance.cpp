//------------ INCLUDES ----------
#include "AnimationInstance.h"
#include "../../../Utility/Debug.h"
#include "../../GameObject/GameObject.h"
#include "AnimationStateContext.h"
#include "../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"

AnimationInstance::AnimationInstance()
	: bPlayAnimation(false)
	, mOwner(nullptr)
{
}

void AnimationInstance::AnimationUpdate()
{
	if (mStateContext)
	{
		mStateContext->Update();
	}
	MainStateMachine();
}


std::weak_ptr<SkeletalMeshAnimationClip> AnimationInstance::LoadAnimationClip(const std::string& _filePath, const std::string& _animationName)
{
	// アニメーションクリップの読み込み
	std::shared_ptr<SkeletalMeshAnimationClip> clip = std::make_shared<SkeletalMeshAnimationClip>();
	clip->Initialize(_filePath);

	clip->SetSkeletalMesh(mSkeletalMesh.lock());

	// アニメーションの読み込みができているか確認
	if (!mAnimationClips.try_emplace(_animationName, clip).second)
	{
		std::cout << "アニメーションが読み込めませんでした" << std::endl;
		return std::weak_ptr<SkeletalMeshAnimationClip>();
	}

	return clip;
}

void AnimationInstance::PlayAnimationClip(const std::string& _animationName, const float _playRate, const float _interpTime, const float _toInterpAnimationClipTime)
{
	// アニメーションプレイヤーへの参照があるかを確認する
	if (!mAnimPlayer.lock()) 
	{
		return;
	}

	// 再生するアニメーションがあるかを確認する
	if (!mAnimationClips.contains(_animationName))
	{
		std::cout << _animationName <<  " アニメーションはありません" << std::endl;
		return;
	}

	std::cout << _animationName << "PlayAnimation" << std::endl;

	mAnimPlayer.lock()->PlayAnimation(mSkeletalMesh.lock(), mAnimationClips[_animationName], _playRate, _interpTime, _toInterpAnimationClipTime);
}

void AnimationInstance::SetOwnerSkeletalMesh(std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	mSkeletalMesh = _skeletalMesh ? _skeletalMesh : nullptr;
}

void AnimationInstance::SetOwner(GameObject* _owner)
{
	mOwner = _owner;
}

GameObject* AnimationInstance::GetOwner()
{
	return mOwner ? mOwner : nullptr;
}

std::shared_ptr<AnimationPlayer> AnimationInstance::GetAnimationPlayer()
{
	return mAnimPlayer.lock();
}


