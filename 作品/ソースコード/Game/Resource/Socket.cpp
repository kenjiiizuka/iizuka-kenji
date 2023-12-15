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

void Socket::Update()
{
	/*float position[3];
	position[0] = mTransform.mPosition.x;
	position[1] = mTransform.mPosition.y;
	position[2] = mTransform.mPosition.z;

	float rotation[3];
	rotation[0] = mTransform.mRotation.x;
	rotation[1] = mTransform.mRotation.y;
	rotation[2] = mTransform.mRotation.z;

	float scale[3];
	scale[0] = mTransform.mScale.x;
	scale[1] = mTransform.mScale.x;
	scale[2] = mTransform.mScale.x;
	
	ImGui::Begin("Socket");
	ImGui::DragFloat3("SocketPosition", position);
	ImGui::DragFloat3("SocketRotation", rotation);
	ImGui::DragFloat3("SocketScale", scale);
	ImGui::End();

	mTransform.mPosition = { position[0], position[1], position[2] };
	mTransform.mRotation = { rotation[0], rotation[1], rotation[2] };
	mTransform.mScale = { scale[0], scale[1], scale[2] };

	mTransformation = MathLibrary::MakeWorldMatrix(mTransform);*/
}

void Socket::CalucBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{
	mBoneMatrix = mTransformation * _parentBoneMatrix;

	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalucBindPoseBoneMatrix(mBoneMatrix);
	}
}

void Socket::CalucAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix)
{
	mBoneMatrix = mTransformation * _parentBoneMatrix;

	for (std::shared_ptr<Bone>& childBone : mChildren)
	{
		childBone->CalucAnimatedBoneMatrix(mBoneMatrix);
	}
}
