//------------- INCLUDES ----------
#include <iostream>
#include "Bone.h"
#include "../../Utility/Debug.h"
#include "../../Utility/MathLibrary.h"
#include "../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

//---------- NAMESPACEALIAS -----------
namespace DXSimpleMath = DirectX::SimpleMath;

Bone::Bone()
	: mBoneColor(0.0f,1.0f,0.0f,1.0f)
	, mBoneRadius(0.05f)
{
	// èàóùÇ»Çµ
}

Bone::~Bone()
{
	// èàóùÇ»Çµ
}

void Bone::Initialize(const std::weak_ptr<BoneAsset> _boneAsset, const std::weak_ptr<Bone> _parentBone, const size_t _numChildren)
{
	if (!_boneAsset.lock())
	{
		std::cout << "BoneAssetÇ…éQè∆Ç™Ç†ÇËÇ‹ÇπÇÒ" << std::endl;
		return;
	}

	mBoneAsset = _boneAsset;
	mParentBone = _parentBone;
	mChildren.resize(_numChildren);
	mBoneName = _boneAsset.lock()->GetBoneName();
	mBindPoseMatrix = mBoneAsset.lock()->GetBindPoseMatrix();
	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone = std::make_shared<Bone>();
	}
}

void Bone::Draw()
{
	// Transform boneWorldTransform;
	// MathLibrary::DecomposeMatrix(mWorldMatrix, boneWorldTransform);
	// DebugRendererManager::GetInstance().DrawSphere(boneWorldTransform.mPosition, mBoneRadius, 1, mBoneColor);
}

void Bone::CalucBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{
	DirectX::SimpleMath::Matrix transformationMatrix = mBoneAsset.lock()->GetTransformationMatrix();
	mBoneMatrix = transformationMatrix * _parentBoneMatrix;

	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalucBindPoseBoneMatrix(mBoneMatrix);
	}
}

void Bone::CalucAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{	
	mBoneMatrix = mAnimationMatrix * _parentBoneMatrix;
	
	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalucAnimatedBoneMatrix(mBoneMatrix);
	}
}

void Bone::CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _parentBoneMatrix)
{
	mWorldMatrix = mBoneMatrix * _parentBoneMatrix;
}

void Bone::AddChildBone(const std::shared_ptr<Bone> _newChildBone)
{
	mChildren.emplace_back(_newChildBone);
}
