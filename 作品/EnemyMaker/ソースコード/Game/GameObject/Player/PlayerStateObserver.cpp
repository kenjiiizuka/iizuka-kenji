//----------- INCLUDES -------------
#include "PlayerStateObserver.h"
#include "PlayerStateController.h"
#include "Player.h"
#include "State/PlayerHitReactionState.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerIdleMoveState.h"
#include "State/PlayerStepState.h"
#include "State/PlayerDeathState.h"

PlayerStateObserver::PlayerStateObserver(Player* _player)
	: mSubjectPlayer(_player)
	, mPrevBehaviorState(PlayerData::PlayerBehaviorState::State_IdleMove)
{
	// 処理なし
}

PlayerStateObserver::~PlayerStateObserver()
{
	// 処理なし
}

void PlayerStateObserver::Initialize(const std::shared_ptr<PlayerStateController> _stateController)
{
	mStateController = _stateController;
	mStateController.lock()->SwitchState<PlayerIdleMoveState>();
}

void PlayerStateObserver::Update()
{
	// ステートの切り替えが必要なのかを判断する
	// 必要ならIdleMoveStateに遷移する
	if (mStateController.lock()->IsNeedTransition())
	{
		// ステート切り替え
		SwitchState(PlayerData::State_IdleMove);
		// ステートを保存
		mPrevBehaviorState = PlayerData::State_IdleMove;
		mSubjectPlayer->SetBehaviorState(mPrevBehaviorState);
		return;
	}

	// 現在のプレイヤーの行動ステートを取得する
	PlayerData::PlayerBehaviorState currentBehaviorState = mSubjectPlayer->GetBehaviorState();

	// 前フレームの状態と同じならリターン
	if (currentBehaviorState == mPrevBehaviorState)
	{
		return;
	}

	// 前フレームと違っていればステート切り替える
	SwitchState(currentBehaviorState);

	// ステートを保存
	mPrevBehaviorState = currentBehaviorState;
}

void PlayerStateObserver::SwitchState(const PlayerData::PlayerBehaviorState& _switchState)
{
	std::shared_ptr<PlayerStateController> validStateController = mStateController.lock();

	if (_switchState == PlayerData::State_Death)
	{
		validStateController->SwitchState<PlayerDeathState>();
	}
	else if (_switchState == PlayerData::State_Attack)
	{
		validStateController->SwitchState<PlayerAttackState>();
	}
	else if (_switchState == PlayerData::State_Step)
	{
		validStateController->SwitchState<PlayerStepState>();
	}
	else if (_switchState == PlayerData::State_HitReaction)
	{
		validStateController->SwitchState<PlayerHitReactionState>();
	}
	// どれでもないなら待機移動ステートに行く
	else
	{
		validStateController->SwitchState<PlayerIdleMoveState>();
	}
}
