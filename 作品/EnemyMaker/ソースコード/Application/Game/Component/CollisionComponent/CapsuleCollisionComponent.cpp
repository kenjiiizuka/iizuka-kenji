//------------ INCLUDES ------------
#include "CapsuleCollisionComponent.h"
#include "../StaticMeshComponent/StaticMesh.h"
#include "../StaticMeshComponent/StaticMeshComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../../System/RendererSystem/Shader/Shader.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../../Resource/Bone.h"
#include "../../Resource/Mesh/CapsuleMesh.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "../../GameObject/GameObject.h"


using namespace DirectX::SimpleMath;

CapsuleCollisionComponent::CapsuleCollisionComponent()
	: PrimitiveComponent(Collision::PrimitiveType_Capsule)
	, mHeight(1.f)
	, mRadius(1.f)
	, mbDebugDraw(false)
{
	// 処理なし
}

void CapsuleCollisionComponent::Init(float _height, float _radius)
{
	mHeight = _height;
	mRadius = _radius;

	// オーナーのワールド行列の取得
	mOwnerWorldMatrix = mOwnerTransform.lock()->GetWorldMatrix();

#ifdef _DEBUG
	mCapsule = std::make_shared<CapsuleMesh>();
	mCapsule->Initialize(mRadius, mHeight, 25, 25);
	mCapsule->SetVisible(true);
#endif
}

void CapsuleCollisionComponent::Draw()
{
#ifdef _DEBUG
	mCapsule->SetMaterialDiffuse(mColor);
	mCapsule->Draw();
#endif
}

void CapsuleCollisionComponent::CalucCollisionTransform()
{
	// Offset行列の作成
	mOffSetTransform.mScale = Vector3(1, 1, 1);
	mOffsetMatrix = MathLibrary::MakeWorldMatrix(mOffSetTransform);

	// ボーンにアタッチされている場合
	if (mAttachedBone.lock())
	{
		Matrix boneMatrix = mAttachedBone.lock()->GetBoneMatrix() * mSkeletalMesh.lock()->GetWorldMatrix();
		mWorldMatrix = mOffsetMatrix * boneMatrix;
	}
	// ボーンにアタッチされていない場合
	else
	{
		mOwnerWorldMatrix = mOwnerTransform.lock()->CalucWorldMatrix(Matrix::Identity);
		mWorldMatrix = mOffsetMatrix * mOwnerWorldMatrix;
	}
	MathLibrary::DecomposeMatrix(mWorldMatrix, mTransform);

#ifdef _DEBUG
	// デバッグ表示
	if (mbDebugDraw)
	{
		mCapsule->SetTransform(mTransform);
	}
	else
	{
		mCapsule->SetVisible(false);
	}
#endif // DEBUG
}

void CapsuleCollisionComponent::SetHeight(const float _height) noexcept
{
	mHeight = _height;
	if (mCapsule)
	{
		mCapsule->SetHeight(_height);
	}	
}

void CapsuleCollisionComponent::SetRadius(const float _radius) noexcept
{
	mRadius = _radius;
	if (mCapsule)
	{
		mCapsule->SetRadius(_radius);
	}	
}
