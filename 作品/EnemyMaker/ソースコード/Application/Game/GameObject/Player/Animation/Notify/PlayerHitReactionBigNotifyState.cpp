//---------- INCLUDES ----------
#include "PlayerHitReactionBigNotifyState.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../GameObject.h"
#include "../../../../Component/TransformComponent/TransformComponent.h"
#include "../../../../../Utility/CurveFloat.h"
#include "../../../../../Utility/MathLibrary.h"

PlayerHitReactionBigNotifyState::PlayerHitReactionBigNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
	, mAttachAnimationDuration(0.0f)
	, mBlowVector(0.0f,0.0f,-1.0f)
{
	// カーブの初期化
	mBlowCurve = std::make_shared<CurveFloat>();
	mBlowCurve->Initialize("assets/Player/Config/BlowCurve.json");
}

PlayerHitReactionBigNotifyState::~PlayerHitReactionBigNotifyState()
{
	// 処理なし
}

void PlayerHitReactionBigNotifyState::NotifyInit()
{
	mPlayerTransform = mSkeletalMesh.lock()->GetOwnerObject()->GetComponent<TransformComponent>();
	mAttachAnimationDuration = mAttachedAnimation->GetDuration();
}

void PlayerHitReactionBigNotifyState::NotifyBegin()
{
	// 吹っ飛び方向とは逆にプレイヤーを向ける
	DirectX::SimpleMath::Vector3 rotation = mPlayerTransform.lock()->GetRotation();
	rotation.y = MathLibrary::Conv_VectorToRotation(mBlowVector).y + PIFloat;
	mPlayerTransform.lock()->SetRotation(rotation);	
}

void PlayerHitReactionBigNotifyState::NotifyUpdate()
{
	// 現在のアニメーションの再生時間を正規化
	float t = mAttachedAnimation->GetCurrentPlayTime() / mAttachAnimationDuration;

	// 吹っ飛びベクトルの取得
	DirectX::SimpleMath::Vector3 blowVector = mBlowVector * mBlowCurve->GetValueByTime(t);

	// プレイヤーを移動
	mPlayerTransform.lock()->AddPosition(blowVector);
}




