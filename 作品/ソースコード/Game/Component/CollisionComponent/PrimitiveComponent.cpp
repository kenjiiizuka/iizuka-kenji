//----------- INCLUDES ----------
#include "PrimitiveComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/InputSystem/Input.h"
#include "../../Resource/Bone.h"

using namespace DirectX::SimpleMath;

PrimitiveComponent::PrimitiveComponent(Collision::PrimitiveType _primitiveType)
	: mScale(Vector3::One)
	, bMoveable(false)
	, bCurrentHit(false)
	, mChannel(Collision::Channel_Movable)
	, mCollisionTypes({
			Collision::Type_Block,
			Collision::Type_Block,
			Collision::Type_Block,
			Collision::Type_Block,
			Collision::Type_Block,
			Collision::Type_Block
		})
	, mPrimitiveType(_primitiveType)
	, mHitColor(0.6f,0.0f,1.0f,1.0f)
	, mDefaultColor(1.0f,1.0f,0.0f,1.0f)
	, mbActiveCollision(true)
	, bCurrentFrameFixOverlap(false)
{	
	mbVisible = true;
	CollisionSystem::GetInstance().RegistrationCollision(this); // コリジョンの登録
}

void PrimitiveComponent::Init()
{
	mOwnerTransform = mOwner->GetComponent<TransformComponent>();
}

void PrimitiveComponent::Uninit()
{
	CollisionSystem::GetInstance().UnRegistrationCollision(this);
}

void PrimitiveComponent::Update(const double _deltaTime)
{	
	bCurrentFrameFixOverlap = false;
	
	mOldPos = mOwnerTransform.lock()->GetPosition();

	// このコリジョンの位置を求める
	CalucCollisionTransform();

	// 現在当たっているかを判断する
	bCurrentHit = (mCurrentHitCollisions.size() != 0);

	if (!mbActiveCollision)
	{
		mColor = {1.0f,1.0f,1.0f,0.2f};
	}
	else if (bCurrentHit)
	{
		mColor = mHitColor;
	}
	else
	{
		mColor = mDefaultColor;
	}
	ExecuteBeginHit();
}

void PrimitiveComponent::LastUpdate()
{
	mPrevHitCollisions = mCurrentHitCollisions;
	mCurrentHitCollisions.clear(); // フレームの終りなのでクリアする
	mBeginHitCollisions.clear();
}

void PrimitiveComponent::CalucCollisionTransform()
{
	mOffSetTransform.mScale = Vector3::One;
	Matrix offsetMatrix = MathLibrary::MakeWorldMatrix(mOffSetTransform);
	Matrix boneMatrix = Matrix::Identity;

	if (mAttachedBone.lock())
	{
		// スケールを除いたボーン行列を作成
		boneMatrix = mAttachedBone.lock()->GetBoneMatrix() * mSkeletalMesh.lock()->GetWorldMatrix();
		Transform boneTrans;
		MathLibrary::DecomposeMatrix(boneMatrix, boneTrans);
		boneTrans.mScale = Vector3::One;
		boneMatrix = MathLibrary::MakeWorldMatrix(boneTrans);
	}

	Transform ownerTrans = mOwnerTransform.lock()->GetTransform();
	ownerTrans.mScale = Vector3::One;
	Matrix ownerMat = MathLibrary::MakeWorldMatrix(ownerTrans);

	mWorldMatrix = offsetMatrix * boneMatrix * ownerMat;
	MathLibrary::DecomposeMatrix(mWorldMatrix, mTransform);
}

void PrimitiveComponent::ExecuteBeginHit()
{
	// このフレームから当たり始めたコリジョンがあるならオーナーのBeginHitを呼ぶ
	for (PrimitiveComponent* beginHit : mBeginHitCollisions)
	{
		mOwner->BeginHit(beginHit->GetOwner(), beginHit);
	}
}


void PrimitiveComponent::FixOverlap(DirectX::SimpleMath::Vector3 _depth)
{
	_depth.y = 0;
	mFixOverlap = _depth;
	mOwnerTransform.lock()->AddPosition(_depth);
	bCurrentFrameFixOverlap = true;
}


std::weak_ptr<Bone> PrimitiveComponent::GetAttachedBone()
{
	return mAttachedBone;
}

void PrimitiveComponent::AttachBone(const std::shared_ptr<Bone> _attachBone, const std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	mAttachedBone = _attachBone;
	mSkeletalMesh = _skeletalMesh;
}

void PrimitiveComponent::AddCurrentHitCollisions(PrimitiveComponent* _currentHitCollision)
{
	// 前フレームに当たっていないコリジョンなら新規に当たったコリジョンとして追加する
	if (std::find(mPrevHitCollisions.begin(), mPrevHitCollisions.end(), _currentHitCollision) == mPrevHitCollisions.end())
	{
		mBeginHitCollisions.emplace_back(_currentHitCollision);
	}
	mCurrentHitCollisions.emplace_back(_currentHitCollision);
}


bool PrimitiveComponent::IsCurrentFrameMoved() const
{
	return  mOldPos != mOwnerTransform.lock()->GetPosition();
}