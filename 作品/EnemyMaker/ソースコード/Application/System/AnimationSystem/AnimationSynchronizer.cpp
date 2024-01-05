//------------- INCLUDES -----------
#include "AnimationSynchronizer.h"
#include "../../Game/Resource/SkeletalMeshAnimationClip.h"
#include "../../Game/Resource/Skeleton.h"
#include "../../Game/Resource/Bone.h"
#include "../../Utility/MathLibrary.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../ImGui/ImGuiUtility.h"
#include "../../Game/Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../Game/Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Utility/Debug.h"
#include "../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

//------------- NAMESPACEALIAS -----------
namespace DXSimpleMath = DirectX::SimpleMath;

AnimationSynchronizer::AnimationSynchronizer()
	: mMeshOwnerObject(nullptr)
	, mbSynchroPosition(false)
	, mbSynchroRotation(false)
	, mbFirstFrame(false)
	, mbRepeated(false)
	, mbDisplacedStartAnimation(false)
	, mbPrevAnimDisplacedStartAnimation(false)
{
	// 処理なし
}

AnimationSynchronizer::~AnimationSynchronizer()
{
	// 処理なし
}

void AnimationSynchronizer::SynchroBegin(std::shared_ptr<SkeletalMesh> _skeletalMesh, const bool _synchroPosition, const bool _synchroRotation, const bool _repeated, const bool _displaced)
{
	mSkeletalMesh = _skeletalMesh;
	mBone = _skeletalMesh->GetSkeleton().lock()->GetRootBone();
	mMeshOwnerObject = _skeletalMesh->GetOwnerObject();

	// 座標同期フラグの設定
	mbRepeated = _repeated;
	mbSynchroPosition = _synchroPosition;
	mbSynchroRotation = _synchroRotation;
	mbFirstFrame = true;
	mbDisplacedStartAnimation = _displaced;

	// アニメーション開始時のSkeletalMeshのワールド行列
	mSkeletalMeshWorldMatrix = _skeletalMesh->GetWorldMatrix();
		
	// スケルタルメッシュのトランスフォームを取得
	mSkeletalMeshTrans = _skeletalMesh->GetWorldTransform();

	// 今のRootボーンの位置を求める
	CalcuRootBoneTransform(mRootBoneTrans);
}

void AnimationSynchronizer::Synchro()
{
	// 参照が有効なのかをチェック
	if (!(mBone.lock() && mSkeletalMesh.lock()))
	{
		return;
	}

	// 連続して同期しており、最初のフレームの処理	
	if (mbFirstFrame)
	{
		SyncSetup();
	}
	
	std::shared_ptr<SkeletalMesh> validSkeletalMesh = mSkeletalMesh.lock();

	// 現在のルートボーンの位置を求める
	Transform currentBoneTrans;
	CalcuRootBoneTransform(currentBoneTrans);

	// 前フレームとの差分を求める
	Transform differenceTrans;
	MathLibrary::CalucTransformDifference(currentBoneTrans, mRootBoneTrans, differenceTrans);
	differenceTrans.mPosition.y = 0.0f;
	differenceTrans.mRotation.x = 0.0f;
	differenceTrans.mRotation.z = 0.0f;

	// 座標同期
	SyncPosition(differenceTrans.mPosition);

	// 回転同期
	SyncRotation(differenceTrans.mRotation);
		
	// コリジョンと同期
	SynchroCollision(currentBoneTrans);
	
	// アニメーション開始位置固定する
	validSkeletalMesh->SetWorldMatrix(mSkeletalMeshWorldMatrix);
	mRootBoneTrans = currentBoneTrans;
	mbFirstFrame = false;
}

void AnimationSynchronizer::AnimationEndSync()
{
	// アニメーション開始位置固定する
	mSkeletalMesh.lock()->SetWorldMatrix(mSkeletalMeshWorldMatrix);
}

void AnimationSynchronizer::SyncPosition(const DirectX::SimpleMath::Vector3& _diffPosition)
{
	// 座標同期しないならリターン
	if (!mbSynchroPosition)
	{
		return;
	}

	// 差分をGameObjectに適応
	std::shared_ptr<TransformComponent> ownerTrans = mMeshOwnerObject->GetComponent<TransformComponent>();

	// 座標同期
	if (mbSynchroPosition)
	{
		ownerTrans->AddPosition(_diffPosition);
	}
}

void AnimationSynchronizer::SyncRotation(const DirectX::SimpleMath::Vector3& _diffRotation)
{
	// 差分をGameObjectに適応
	std::shared_ptr<TransformComponent> ownerTrans = mMeshOwnerObject->GetComponent<TransformComponent>();

	if (mbSynchroRotation)
	{
		if (!mbFirstFrame)
		{
			ownerTrans->AddRotation(_diffRotation);
		}
	}
}

void AnimationSynchronizer::SynchroCollision(Transform& _rootBoneTrans)
{
	// コリジョンがあるかを確認
	// 現状カプセルだけなのでカプセルコリジョンがあるか確認する
	std::shared_ptr<CapsuleCollisionComponent> capsule = mMeshOwnerObject->GetComponent<CapsuleCollisionComponent>();

	if (!capsule)
	{
		return;
	}

	// 現フレームでコリジョンにめり込みがあり修正されていたら、その分アニメーションも動かす
	if (!capsule->IsCurrentFrameFixOverlap())
	{
		return;
	}

	// 修正されていた分SkeletalMeshを動かす
	// RootBoneの動きに同期させているので、GameObjectとRootBoneの位置の差分だけ移動させる
	DXSimpleMath::Vector3 fixVector = mMeshOwnerObject->GetComponent<TransformComponent>()->GetPosition() - _rootBoneTrans.mPosition;
	fixVector.y = 0;
	DXSimpleMath::Matrix fixTranslation;
	MathLibrary::CreateTranslationMatrix(fixVector, fixTranslation);
	mSkeletalMeshWorldMatrix *= fixTranslation;

	// 移動後のRootBoneの位置を計算
	DXSimpleMath::Matrix currentBoneMatrix = mBone.lock()->GetBoneMatrix() * mSkeletalMeshWorldMatrix;
	MathLibrary::DecomposeMatrix(currentBoneMatrix, _rootBoneTrans);
}

void AnimationSynchronizer::RepeatSynchroSetup()
{	
	// スケルタルメッシュの位置を再計算
	std::shared_ptr<SkeletalMeshComponent> skeletalMeshComp = mMeshOwnerObject->GetComponent<SkeletalMeshComponent>();
	DXSimpleMath::Matrix meshCompMatrix = MathLibrary::MakeWorldMatrix(skeletalMeshComp->GetTransform());
	DXSimpleMath::Matrix meshOwnerMatrix = mMeshOwnerObject->GetComponent<TransformComponent>()->CalucWorldMatrix(DXSimpleMath::Matrix::Identity);
	mSkeletalMesh.lock()->CalucWorldMatrix(meshCompMatrix * meshOwnerMatrix);
	mSkeletalMeshWorldMatrix = mSkeletalMesh.lock()->GetWorldMatrix();
	mSkeletalMeshTrans = mSkeletalMesh.lock()->GetWorldTransform();

	// 今のRootボーンの位置を求める
	CalcuRootBoneTransform(mRootBoneTrans);
}

void AnimationSynchronizer::SyncSetup()
{
	// 開始からルートの位置がずれいるアニメーションに関してはこの処理はしない
	if (mbRepeated && !mbDisplacedStartAnimation)
	{
		RepeatSynchroSetup();
	}

	// RootBoneへの差分を計算
	CalcuObjectToRootBoneVector();
}

void AnimationSynchronizer::CalcuObjectToRootBoneVector()
{
	// ルートボーンの位置を計算
	Transform rootBoneTrans;
	CalcuRootBoneTransform(rootBoneTrans);

	// オーナーのGameObjectのポジションを取得
	DXSimpleMath::Vector3 ownerPosition = mMeshOwnerObject->GetComponent<TransformComponent>()->GetPosition();

	// GameObjectとRootBoneの差分を求める
	mObjectToRootBone = rootBoneTrans.mPosition - ownerPosition;
}

void AnimationSynchronizer::CalcuRootBoneTransform(Transform& _transform)
{
	std::shared_ptr<Bone> validBone = mBone.lock();
	DXSimpleMath::Matrix currentBoneMatrix = validBone->GetBoneMatrix() * mSkeletalMeshWorldMatrix;
	MathLibrary::DecomposeMatrix(currentBoneMatrix, _transform);
}
