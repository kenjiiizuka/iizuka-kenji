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
	// �����Ȃ�
}

PlayerStateObserver::~PlayerStateObserver()
{
	// �����Ȃ�
}

void PlayerStateObserver::Initialize(const std::shared_ptr<PlayerStateController> _stateController)
{
	mStateController = _stateController;
	mStateController.lock()->SwitchState<PlayerIdleMoveState>();
}

void PlayerStateObserver::Update()
{
	// �X�e�[�g�̐؂�ւ����K�v�Ȃ̂��𔻒f����
	// �K�v�Ȃ�IdleMoveState�ɑJ�ڂ���
	if (mStateController.lock()->IsNeedTransition())
	{
		// �X�e�[�g�؂�ւ�
		SwitchState(PlayerData::State_IdleMove);
		// �X�e�[�g��ۑ�
		mPrevBehaviorState = PlayerData::State_IdleMove;
		mSubjectPlayer->SetBehaviorState(mPrevBehaviorState);
		return;
	}

	// ���݂̃v���C���[�̍s���X�e�[�g���擾����
	PlayerData::PlayerBehaviorState currentBehaviorState = mSubjectPlayer->GetBehaviorState();

	// �O�t���[���̏�ԂƓ����Ȃ烊�^�[��
	if (currentBehaviorState == mPrevBehaviorState)
	{
		return;
	}

	// �O�t���[���ƈ���Ă���΃X�e�[�g�؂�ւ���
	SwitchState(currentBehaviorState);

	// �X�e�[�g��ۑ�
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
	// �ǂ�ł��Ȃ��Ȃ�ҋ@�ړ��X�e�[�g�ɍs��
	else
	{
		validStateController->SwitchState<PlayerIdleMoveState>();
	}
}
