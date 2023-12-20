#include "PlayerAttackState.h"
#include "../PlayerAttackData.h"
#include "../Player.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Component/PlayerInputComponent/PlayerInputContollerComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../../System/InputSystem/XInput.h"

PlayerAttackState::PlayerAttackState(Player* _player)
	: PlayerStateContext(_player)
{
	// 処理なし
}

PlayerAttackState::~PlayerAttackState()
{
	// 処理なし
}

void PlayerAttackState::Entry()
{
	// 入力不可状態にする
	mbIsInputAble = false;

	// 攻撃データを取得する
	mAttackData = mPlayer->GetAttackData();

	// インプットコントローラーを取得する
	std::shared_ptr<PlayerInputControllerComponent> inputController = mPlayer->GetControllerComponent().lock();
	
	// プレイヤーのする攻撃をセットする
	PlayerAttack attack;
	if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackB))
	{
		attack = mAttackData.lock()->GetNextBAttackInformation(PlayerData::AttackID_NoAttack);
	}
	else if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackY))
	{
		attack = mAttackData.lock()->GetNextYAttackInformation(PlayerData::AttackID_NoAttack);
	}
	mPlayer->SetCurrentAttack(attack);
	mPlayer->SetNextAttackInterpTime(0.0f);
	mPlayer->SetNextAttackInterpStartTime(0.0f);
	mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);

	mInputController = inputController;
}

void PlayerAttackState::Update()
{
	// 攻撃アニメーションが終っていないかを確認
	// 終っていれば攻撃していない状態をセットしてリターン
	if(CheckAttackAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	// 入力可能かを判断
	mbIsInputAble = CheckInputAble();

	// 入力可能ならコンボの処理をする
	if (mbIsInputAble)
	{
		Comb();
	}
}

void PlayerAttackState::Exit()
{
	PlayerAttack noAttack = mAttackData.lock()->GetAttack(PlayerData::AttackID_NoAttack);
	mPlayer->SetAttackAble(true);
	mPlayer->SetCurrentAttack(noAttack);
	mPlayer->SetNextAttackInterpTime(0.0f);
}

bool PlayerAttackState::CheckAttackAnimationEnd()
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<AnimationPlayer> animPlayer = animationInstance->GetAnimationPlayer();
	
	// 再生されていない、次のフレームで終了する場合はtrueを返す
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());	
}

bool PlayerAttackState::CheckInputAble()
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();

	// アニメーションが再生されているかを確認　再生されていなかったらtrue
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

void PlayerAttackState::Comb()
{
	// 入力があれば次の攻撃の情報を取得する
	PlayerData::AttackID currentAttackID = mPlayer->GetCurrentAttackID();	

	std::shared_ptr<PlayerInputControllerComponent> inputController = mInputController.lock();

	// ボタンの入力に合わせて攻撃のデータをセットする
	if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackY))
	{
		// 次の攻撃がなければ攻撃不可にする
		PlayerData::AttackID nextY = mAttackData.lock()->GetAttack(currentAttackID).mNextY;
		if (nextY == PlayerData::AttackID_NoAttack)
		{
			mPlayer->SetAttackAble(false);
			return;
		}

		// 次の攻撃の設定
		PlayerAttack attack = mAttackData.lock()->GetNextYAttackInformation(currentAttackID);
		mPlayer->SetCurrentAttack(attack);
 
		// 直前の攻撃を取得
		PlayerAttack prevAttack = mPlayer->GetPrevAttack();

		// 次のアニメーションまで補間にかける時間を設定 
		mPlayer->SetNextAttackInterpTime(prevAttack.mAnimationInterp.mYAttackInterpTime);

		mPlayer->SetNextAttackInterpStartTime(prevAttack.mAnimationInterp.mYAttackInterpStartTime);

		// アイドルへの補間にかける時間のセット
		mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);
	}
	else if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackB))
	{
		// 次の攻撃がなければ攻撃不可にする
		PlayerData::AttackID nextB = mAttackData.lock()->GetAttack(currentAttackID).mNextB;
		if (nextB == PlayerData::AttackID_NoAttack)
		{
			mPlayer->SetAttackAble(false);
			return;
		}

		// 次の攻撃の設定
		PlayerAttack attack = mAttackData.lock()->GetNextBAttackInformation(currentAttackID);
		mPlayer->SetCurrentAttack(attack);

		PlayerAttack prevAttack = mPlayer->GetPrevAttack();

		// 次のアニメーションまで補間にかける時間を設定 
		mPlayer->SetNextAttackInterpTime(prevAttack.mAnimationInterp.mBAttackInterpTime);

		// 次にアニメーションの補間開始位置の設定
		mPlayer->SetNextAttackInterpStartTime(prevAttack.mAnimationInterp.mBAttackInterpStartTime);

		// アイドルへの補間にかける時間のセット
		mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);
	}	
}
