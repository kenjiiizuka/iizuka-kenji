//------------ INCLUDES -----------
#include "PlayerIdleMoveState.h"
#include "../Player.h"
#include "../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../../System/InputSystem/XInput.h"
#include "../../../../ImGui/ImGuiUtility.h"

PlayerIdleMoveState::PlayerIdleMoveState(Player* _player)
	: PlayerStateContext(_player)
{
	// 処理なし
}

PlayerIdleMoveState::~PlayerIdleMoveState()
{
	// 処理なし
}

void PlayerIdleMoveState::Entry()
{
	mbIsInputAble = true;
	mMoveComp = mPlayer->GetComponent<PlayerMovementComponent>();

	// IdleMoveになったら、直前にしていた攻撃をNoAttackに設定する
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
	// レフトスティックが入力されていない時はリターン
	if (!XInput::IsLeftStickInputAble())
	{
		return;
	}

	DirectX::SimpleMath::Vector3 direction = mPlayer->GetCameraAlignedLStickDirection();
	mMoveComp.lock()->AddMovementInput(direction);
}
