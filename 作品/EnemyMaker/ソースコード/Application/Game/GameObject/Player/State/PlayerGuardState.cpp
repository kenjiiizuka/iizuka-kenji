//---------- INCLUDES ---------
#include "PlayerGuardState.h"
#include "../Player.h"
#include "../../../Component/PlayerInputComponent/PlayerInputContollerComponent.h"
#include "../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"

PlayerGuardState::PlayerGuardState(Player* _player)
	: PlayerStateContext(_player)
	, mGuardStartElapsedTime(0.0f)
	, mJustGuardSuccessTime(0.3f)
	, mbGuardEnd(false)
{
	// 処理なし
}

PlayerGuardState::~PlayerGuardState()
{
	// 処理なし
}

void PlayerGuardState::Entry()
{
	mbIsInputAble = false;
	mInputController = mPlayer->GetComponent<PlayerInputControllerComponent>();
	mPlayer->SetGuardInput(true);
}

void PlayerGuardState::Update()
{
	// 入力が終了していれば、ステートの終了遷移の判断をする　
	if (mbGuardEnd)
	{
		// アニメーションが終了していればステートを変更する
		if (CheckGuardAnimationFinish())
		{
			mbIsInputAble = true;
			mbNeedTransitionState = true;
		}
		
		// 移動入力があれば終了
		if (XInput::IsLeftStickInputAble())
		{
			DirectX::SimpleMath::Vector3 direction = mPlayer->GetCameraAlignedLStickDirection();
			mPlayer->GetComponent<PlayerMovementComponent>()->AddMovementInput(direction);
			mbIsInputAble = true;
			mbNeedTransitionState = true;
		}
	}

	// ガードの入力が終っているかを確認する
	if (!mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_Guard))
	{
		mbGuardEnd = true;
		mbIsInputAble = true;
		mPlayer->SetGuardInput(false);
	}

	mGuardStartElapsedTime += mPlayer->GetCustomDeltaTime();
}

void PlayerGuardState::Exit()
{
	mPlayer->SetGuardInput(false);
}

bool PlayerGuardState::CheckGuardAnimationFinish()
{
	std::shared_ptr<AnimationPlayer> animPlayer = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance()->GetAnimationPlayer();
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}

PlayerData::GuardResult PlayerGuardState::CheckGuard(const DirectX::SimpleMath::Vector3 _attackPosition) const noexcept
{
	std::shared_ptr<TransformComponent> playerTrans = mPlayer->GetComponent<TransformComponent>();

	// プレイヤーから攻撃位置への単位ベクトルを計算
	DirectX::SimpleMath::Vector3 toAttack = _attackPosition - playerTrans->GetPosition();
	toAttack.Normalize();

	// 攻撃方向とプレイヤーの前向きベクトルの内積が、ガード可能範囲を超えていないかを判断する
	float dot = playerTrans->GetForwardVector().Dot(toAttack);

	// 仮で180度ガード可能
	if (dot >= 0.0)
	{
		// ジャスガできているかの確認
		if (mGuardStartElapsedTime <= mJustGuardSuccessTime)
		{
			return PlayerData::GuardResult::Result_JustGuard;
		}

		// 通常ガード
		return PlayerData::GuardResult::Result_Guard;
	}

	// ガード失敗
	return PlayerData::GuardResult::Result_Faild;
}

