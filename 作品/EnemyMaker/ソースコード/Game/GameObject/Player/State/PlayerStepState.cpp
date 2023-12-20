//---------- INCLUDES ------------
#include "PlayerStepState.h"
#include "../Player.h"
#include "../Animation/PlayerAnimationInstance.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../../Utility/MathLibrary.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"


PlayerStepState::PlayerStepState(Player* _player)
	: PlayerStateContext(_player)
{
	// 処理なし
}

PlayerStepState::~PlayerStepState()
{
	// 処理なし
}

void PlayerStepState::Entry()
{
	mbIsInputAble = false;

	// 直前に行っていたプレイヤーの攻撃を取得
	PlayerAttack attack = mPlayer->GetPrevAttack();

	// 攻撃していなければ通常ステップ
	if (attack.mAttackID == PlayerData::AttackID_NoAttack)
	{
		mPlayer->SetStepAnimationClipName("Roll");
		mPlayer->SetStepAnimationInterpStartTime(8.0f);
		mPlayer->SetIdleRunInterpTime(mPlayer->GetStepToIdleRunInterpTime());
		return;
	}

	// プレイヤーの右向きベクトルと左スティックの倒れている方向を取得
	DirectX::SimpleMath::Vector3 rotation = mPlayer->GetComponent<TransformComponent>()->GetRotation();	
	DirectX::SimpleMath::Vector3 right = MathLibrary::GetRightVector(rotation);
	DirectX::SimpleMath::Vector3 controllerLStickDirection = mPlayer->GetCameraAlignedLStickDirection();
	controllerLStickDirection.Normalize();

	// 右向きベクトルとスティックの倒れている方向で内積をとり左右どちらのステップをするか判定する
	float dot = right.Dot(controllerLStickDirection);
	
	// 右ステップ
	if (MathLibrary::InRange(dot, 0.75f, 1.0f))
	{
		// 使用するステップアニメーションクリップ名のセット
		mPlayer->SetStepAnimationClipName(attack.mRightStepAnimationClipName);  
		// 補間にかける時間のセット
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mRightStepInterpTime);
		// 補間先位置のセット
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mRightStepInterpStartTime);
		// Idleへの補間にかける時間のセット
		mPlayer->SetIdleRunInterpTime(mPlayer->GetRightStepToIdleRunInterpTime());
	}
	// 左ステップ
	else if (MathLibrary::InRange(dot, -1.0f, -0.75f))
	{
		// 使用するステップアニメーションクリップ名のセット
		mPlayer->SetStepAnimationClipName(attack.mLeftStepAnimationClipName);
		// 補間にかける時間のセット
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mLeftStepInterpTime);
		// 補間先位置のセット
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mLeftStepInterpStartTime);
		// Idleへの補間にかける時間のセット
		mPlayer->SetIdleRunInterpTime(mPlayer->GetLeftStepToIdleRunInterpTime());
	}
	// 通常ステップ
	else
	{
		// 使用するステップアニメーションクリップ名のセット
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mStepInterpStartTime);
		// 補間にかける時間のセット
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mStepInterpTime);
		// 補間先位置のセット
		mPlayer->SetStepAnimationClipName(attack.mStepAnimationClipName);
		// Idleへの補間にかける時間のセット
		mPlayer->SetIdleRunInterpTime(mPlayer->GetStepToIdleRunInterpTime());
	}
}

void PlayerStepState::Update()
{
	if (CheckAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	mbIsInputAble = CheckInputAble();
}

bool PlayerStepState::CheckAnimationEnd()
{
	std::shared_ptr<AnimationPlayer> animPlayer = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance()->GetAnimationPlayer();
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}

bool PlayerStepState::CheckInputAble() const
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();

	// アニメーションが再生されているかを確認
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = animationInstance->GetAnimationPlayer()->GetPlayAnimation().lock();
	if (!animClip)
	{
		return true;
	}

	// 通知がついているか確認ついてなければ入力不可
	std::shared_ptr<PlayerInputAbleNotifyState> notify = animClip->GetAnimnotifyState<PlayerInputAbleNotifyState>();
	if (!notify)
	{
		return false;
	}

	// 通知があれば通知から入力可能かを受け取る
	return notify->IsInputAble();
}
