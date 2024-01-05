#include "TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

TransformComponent::TransformComponent()
	: bPositionParentInfluence(true)
	, bRotationParentInfluence(true)
	, bScaleParentInfluence(true)
{
}

DirectX::SimpleMath::Matrix TransformComponent::CalucWorldMatrix(DirectX::SimpleMath::Matrix _parent)
{
	DirectX::SimpleMath::Matrix scale, rot, trans;
	scale = DirectX::SimpleMath::Matrix::CreateScale(mTransform.mScale.x, mTransform.mScale.y, mTransform.mScale.z);                   // ägëÂèkè¨
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mTransform.mRotation.y, mTransform.mRotation.x, mTransform.mRotation.z); // âÒì]
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mPosition.z);    // ïΩçsà⁄ìÆ
	mWorldMatrix = scale * rot * trans;

	// êeÇÃâeãøÇéÛÇØÇÈÇ©
	if (bPositionParentInfluence && bRotationParentInfluence && bScaleParentInfluence)
	{
		mWorldMatrix = mWorldMatrix * _parent;
		return mWorldMatrix;
	}
	
	Transform parentTrasform;
	MathLibrary::DecomposeMatrix(_parent, parentTrasform);
	
	if (bScaleParentInfluence)
	{
		scale *= Matrix::CreateScale(parentTrasform.mScale.x, parentTrasform.mScale.y, parentTrasform.mScale.z);
	}	
	if (bRotationParentInfluence)
	{
		rot *= Matrix::CreateFromYawPitchRoll(parentTrasform.mRotation.y, parentTrasform.mRotation.x, parentTrasform.mRotation.z);
	}	
	if (bPositionParentInfluence)
	{
		trans *= Matrix::CreateTranslation(parentTrasform.mPosition.x, parentTrasform.mPosition.y, parentTrasform.mPosition.z);
	}
	mWorldMatrix = scale * rot * trans;

	return mWorldMatrix;
}

void TransformComponent::SetWorldMatrix(DirectX::SimpleMath::Matrix _world)
{
	mWorldMatrix = _world;
	MathLibrary::DecomposeMatrix(mWorldMatrix, mTransform);
}