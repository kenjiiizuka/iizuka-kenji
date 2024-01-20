//---------- INCLUDES -----------
#include <iostream>
#include "Socket.h"
#include "../../Utility/MathLibrary.h"
#include "../../ImGui/ImGuiUtility.h"

Socket::Socket()
{
	mBoneColor = { 1.0f,0.0f,0.0f,1.0f };
	mBoneRadius = 0.1f;
}

Socket::~Socket()
{
	// èàóùÇ»Çµ
}

void Socket::Initialize(const Transform& _transform, const std::string& _socketName, const std::shared_ptr<Bone> _parentBone)
{
	mTransform = _transform;
	mBoneName = _socketName;
	mTransformation = MathLibrary::MakeWorldMatrix(_transform);
	mParentBone = _parentBone;
}

void Socket::CalcuBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{
	mBoneMatrix = mTransformation * _parentBoneMatrix;

	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalcuBindPoseBoneMatrix(mBoneMatrix);
	}
}

void Socket::CalcuAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{
	mBoneMatrix = mTransformation * _parentBoneMatrix;

	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalcuAnimatedBoneMatrix(mBoneMatrix);
	}
}
