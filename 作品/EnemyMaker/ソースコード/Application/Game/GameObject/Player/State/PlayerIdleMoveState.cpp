//------------ INCLUDES -----------
#include "PlayerIdleMoveState.h"
#include "../Player.h"
#include "../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../../System/InputSystem/XInput.h"
#include "../../../../ImGui/ImGuiUtility.h"

PlayerIdleMoveState::PlayerIdleMoveState(Player* _player)
	: PlayerStateContext(_player)
{
	// �����Ȃ�
}

PlayerIdleMoveState::~PlayerIdleMoveState()
{
	// �����Ȃ�
}

void PlayerIdleMoveState::Entry()
{
	mbIsInputAble = true;
	mMoveComp = mPlayer->GetComponent<PlayerMovementComponent>();

	// IdleMove�ɂȂ�����A���O�ɂ��Ă����U����NoAttack�ɐݒ肷��
	PlayerAttack noAttack = mPlayer->GetAttackData().lock()->GetAttack(PlayerData::AttackID_NoAttack);
	mPlayer->SetAttackAble(true);
	mPlayer->SetCurrentAttack(noAttack);
}

void PlayerIdleMoveState::Exit()
{
	mMoveComp.lock()->MoveStop();
}

void PlayerIdleMoveState::Update()
{
	// ���t�g�X�e�B�b�N�����͂���Ă��Ȃ����̓��^�[��
	if (!XInput::IsLeftStickInputAble())
	{
		return;
	}

	DirectX::SimpleMath::Vector3 direction = mPlayer->GetCameraAlignedLStickDirection();
	mMoveComp.lock()->AddMovementInput(direction);
}
